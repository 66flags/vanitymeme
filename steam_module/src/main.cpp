#include "includes.hpp"

SafetyHookInline g_create_process_hk{ };

int __stdcall create_process_hk( LPCWSTR lpApplicationName, LPWSTR lpCommandLine, LPSECURITY_ATTRIBUTES lpProcessAttributes, LPSECURITY_ATTRIBUTES lpThreadAttributes, BOOL bInheritHandles, DWORD dwCreationFlags, LPVOID lpEnvironment, LPCWSTR lpCurrentDirectory, LPSTARTUPINFOW lpStartupInfo, LPPROCESS_INFORMATION lpProcessInformation )
{
    if ( !lpApplicationName )
        return g_create_process_hk.stdcall< int >( lpApplicationName, lpCommandLine, lpProcessAttributes, lpThreadAttributes, bInheritHandles, dwCreationFlags, lpEnvironment, lpCurrentDirectory, lpStartupInfo, lpProcessInformation );

    auto original = g_create_process_hk.stdcall< int >( lpApplicationName, lpCommandLine, lpProcessAttributes, lpThreadAttributes, bInheritHandles, dwCreationFlags, lpEnvironment, lpCurrentDirectory, lpStartupInfo, lpProcessInformation );

    std::wstring app_name{ lpApplicationName };
    spdlog::info( "Process created: {}", std::string( app_name.begin( ), app_name.end( ) ) );
    if ( !wcsstr( lpApplicationName, L"Counter-Strike Global Offensive\\csgo.exe" ) )
        return original;

    auto handle = lpProcessInformation->hProcess;

    if ( !handle ) {
        spdlog::error( "Failed to get process handle" );
        return original;
    }

    // hl2_10EC0000_00084BB0
    auto allocated = VirtualAllocEx( handle, reinterpret_cast< void * >( 0x19B30000 ),
                                     0x0794000,
                                     MEM_COMMIT | MEM_RESERVE,
                                     PAGE_EXECUTE_READWRITE );

    if ( !allocated ) {
        spdlog::error( "Failed to allocate memory in target process." );
        return original;
    }

    spdlog::info( "Allocated memory at {}", allocated );

    return original;
}

void __stdcall hooks_main( HMODULE mod )
{
    FILE *stream = nullptr;

    AllocConsole( );
    freopen_s( &stream, "CONOUT$", "w", stdout );
    SetConsoleTitleA( "VANITY steam" );

    auto address = reinterpret_cast< void * >( GetProcAddress( GetModuleHandleA( "kernel32.dll" ), "CreateProcessW" ) );

    g_create_process_hk = safetyhook::create_inline( address, reinterpret_cast< void * >( create_process_hk ) );

    while ( !GetAsyncKeyState( VK_END ) )
        std::this_thread::sleep_for( std::chrono::milliseconds( 250 ) );

    FreeConsole( );
    FreeLibraryAndExitThread( mod, 0 );
}

int __stdcall DllMain( HINSTANCE mod, unsigned long reason, void *reserved )
{
    if ( reason == DLL_PROCESS_ATTACH ) {
        auto thread = CreateThread( nullptr, 0, LPTHREAD_START_ROUTINE( hooks_main ), mod, 0, nullptr );

        if ( thread )
            CloseHandle( thread );
    }

    return 1;
}