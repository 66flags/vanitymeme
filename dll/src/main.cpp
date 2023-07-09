#include "includes.hpp"

SafetyHookInline g_connect_hk{ };
SafetyHookInline g_config_handler_hk{ };
SafetyHookInline g_curl_easy_setopt_hk{ };
SafetyHookInline g_read_packet_hk{ };
SafetyHookInline g_send_packet_hk{ };
SafetyHookInline g_checkbox_hk{ };

uintptr_t allocated = 0;

char lol[ 20 ];
bool __cdecl checkbox_hk( const char *label, bool *v )
{
    // wanted ret 0x19CFBB70
    // checkbox add 0x19D25690
    // inputtext 0x19CA6DC0

    bool result = g_checkbox_hk.call< bool >( label, v );

    // in misc
    if ( reinterpret_cast< uintptr_t >( _ReturnAddress( ) ) == ( allocated + 0x1CBB70 ) ) {
        static auto input_text = reinterpret_cast< int( __cdecl * )( void *icon, const char *label, char *buf, int buf_size, int flags, int callback, void *userdata ) >( reinterpret_cast< void * >( allocated + 0x176DC0 ) );

        if ( input_text( reinterpret_cast< void * >( allocated + 0x4B0288 ), "Menu username", lol, sizeof( lol ), 0, 0, 0 ) )
            memmove( reinterpret_cast< void * >( allocated + 0x74AA44 ), lol, sizeof( lol ) );
    }

    return result;
}

int __cdecl connect_hk( const char *a1, unsigned __int16 a2 )
{
    WSADATA data;

    if ( WSAStartup( MAKEWORD( 2, 2 ), &data ) )
        return 0;

    if ( data.wVersion == 514 ) {
        sockaddr_in sa;

        sa.sin_family = 2;
        sa.sin_port = ntohs( 12563 );
        sa.sin_addr.s_addr = inet_addr( "127.0.0.1" );

        auto socket_a = socket( 2, 1, 6 );

        if ( socket_a == -1 ) {
            return 0;
        } else if ( connect( socket_a, ( const sockaddr * ) &sa, 0x10 ) == -1 ) {
            return 0;
        } else {
            return socket_a;
        }
    } else {
        WSACleanup( );
    }
}

int __cdecl read_packet( SOCKET s, int a2, int a3 )
{
    auto original = g_read_packet_hk.call< int >( s, a2, a3 );

    spdlog::info( "Read: {}", reinterpret_cast< void * >( _ReturnAddress( ) ) );

    return original;
}

int __cdecl send_packet( SOCKET s, int a2, int a3 )
{
    auto original = g_send_packet_hk.call< int >( s, a2, a3 );

    spdlog::info( "Send: {}", reinterpret_cast< void * >( _ReturnAddress( ) ) );

    return original;
}

const char *__cdecl config_handler( int a1, int a2 )
{
    auto original = g_config_handler_hk.call< const char * >( a1, a2 );

#if 0
    spdlog::info( "Config handler called. {}", original );
#endif

    return original;
}

int __cdecl curl_easy_setopt( int a1, void *Src, const char *a3 )
{
    auto original = g_curl_easy_setopt_hk.call< int >( a1, Src, a3 );

    if ( !a3 ) {
        spdlog::error( "Invalid string." );
        return original;
    }

    spdlog::info( "Config handler called. {}", original );

    return original;
}

void fix_relocations( uintptr_t allocated, uintptr_t dump2_base )
{
    uintptr_t delta = allocated - dump2_base;

    for (uintptr_t i = 0; i < relocations.size(); i++) {
        auto a = ( void * )( allocated + relocations.at( i ) );

        spdlog::info( "{} {}", a, delta );
        *reinterpret_cast< uintptr_t * >( allocated + relocations.at( i ) ) += delta;
    }

}

#define MAIN_IMAGE_BASE 0x19B30000

void __stdcall hooks_main( )
{
    FILE *stream = nullptr;

    AllocConsole( );
    freopen_s( &stream, "CONOUT$", "w", stdout );

    while ( !GetModuleHandleA( "serverbrowser.dll" ) )
        std::this_thread::sleep_for( std::chrono::milliseconds( 400 ) );

    spdlog::info( "Allocating cheat memory..." );
                    
    allocated = reinterpret_cast< uintptr_t >( VirtualAlloc( nullptr,
                                                             0x0794000,
                                                             MEM_COMMIT | MEM_RESERVE,
                                                             PAGE_EXECUTE_READWRITE ) );

    if ( !allocated ) {
        spdlog::error( "Failed to allocate memory in process." );
        return;
    }

    spdlog::info( "{}", reinterpret_cast< void * >( allocated ) );

    memcpy( reinterpret_cast< void * >( allocated ), vanity_bin, sizeof( vanity_bin ) );

    spdlog::info( "Fixing relocations..." );

    fix_relocations( allocated, 0x19B30000 );

    spdlog::info( "Fixing imports..." );

    for ( auto &_import : g_imports_list ) {
        auto import_dll = LoadLibraryA( std::get< 1 >( _import ) );

        if ( !import_dll ) {
            spdlog::error( "Failed to resolve dll {}.", std::get< 1 >( _import ) );
            continue;
        }

        auto export_proc = GetProcAddress( import_dll, std::get< 2 >( _import ) );

        if ( !import_dll ) {
            spdlog::error( "Failed to resolve import {}->{}.", std::get< 1 >( _import ), std::get< 2 >( _import ) );
            continue;
        }

        auto offset = std::get< 0 >( _import ) - MAIN_IMAGE_BASE;

        *reinterpret_cast< uint32_t * >( allocated + offset ) = ( uint32_t ) export_proc;
    }

    spdlog::info( "Patching calls..." );

    memset( reinterpret_cast< void * >( allocated + 0x1BEF15 ), 0x90, 5 );
    memset( reinterpret_cast< void * >( allocated + 0x590F6 ), 0x90, 5 );
    memset( reinterpret_cast< void * >( allocated + 0xFE3C3 ), 0x90, 5 );
    memset( reinterpret_cast< void * >( allocated + 0x104030 ), 0x90, 5 );
    memset( reinterpret_cast< void * >( allocated + 0x5912C ), 0x90, 5 );

    memset( reinterpret_cast< void * >( allocated + 0x1D047F ), 0x90, 5 );
    memset( reinterpret_cast< void * >( allocated + 0x1D04EB ), 0x90, 5 );
    memset( reinterpret_cast< void * >( allocated + 0x1D05F6 ), 0x90, 5 );
    memset( reinterpret_cast< void * >( allocated + 0x1D03AA ), 0x90, 5 );
    // memset( reinterpret_cast< void * >( 0x19B891C1 ), 0x90, 59 );

    *reinterpret_cast< int * >( reinterpret_cast< void * >( allocated + 0x56A5E8 ) ) = 1337;

    g_send_packet_hk = safetyhook::create_inline( reinterpret_cast< void * >( allocated + 0x76CE0 ), reinterpret_cast< void * >( send_packet ) );
    g_read_packet_hk = safetyhook::create_inline( reinterpret_cast< void * >( allocated + 0x76D40 ), reinterpret_cast< void * >( read_packet ) );
    g_connect_hk = safetyhook::create_inline( reinterpret_cast< void * >( allocated + 0x76B00 ), reinterpret_cast< void * >( connect_hk ) );

    g_curl_easy_setopt_hk = safetyhook::create_inline( reinterpret_cast< void * >( allocated + 0x278F40 ), reinterpret_cast< void * >( curl_easy_setopt ) );
    g_config_handler_hk = safetyhook::create_inline( reinterpret_cast< void * >( allocated + 0x114170 ), reinterpret_cast< void * >( config_handler ) );
    g_checkbox_hk = safetyhook::create_inline( reinterpret_cast< void * >( allocated + 0x1F5690 ), reinterpret_cast< void * >( checkbox_hk ) );

    MessageBoxA( nullptr, "Click ok to fucking die", "", MB_OK );

    reinterpret_cast< void( __cdecl * )( ) >( reinterpret_cast< void * >( allocated + 0x3058D5 ) )( );// security init cookie
    reinterpret_cast< int( __cdecl * )( HINSTANCE, DWORD, LPVOID ) >( reinterpret_cast< void * >( allocated + 0x304E64 ) )( reinterpret_cast< HINSTANCE >( allocated ), DLL_PROCESS_ATTACH, 0 );

    static std::vector< config_data_t > parsed_cfg;

    config_data_t new_cfg{ };
    strcpy( new_cfg.loaded_config, "seven" );
    strcpy( new_cfg.config_name, "nine" );
    strcpy( new_cfg.owner_name, "eight" );
    new_cfg.is_public = false;
    new_cfg.is_user_config = true;
    new_cfg.should_delete = false;
    new_cfg.is_liked = true;
    new_cfg.user_id = 1337;
    new_cfg.rating = 100;
    new_cfg.downloads = 5000;
    new_cfg.category = 2;

    parsed_cfg.push_back( new_cfg );

    strcpy( new_cfg.config_name, "seven" );
    new_cfg.category = 0;

    parsed_cfg.push_back( new_cfg );
    
    strcpy( new_cfg.config_name, "four" );
    new_cfg.category = 1;

    parsed_cfg.push_back( new_cfg );

    // C7 85 BC C1 FF FF "54 A8 09 1A"
    // mov  dword ptr [ebp-3E44h], offset "g_menu_config_vector"
    // first 4 bytes of vectors have a ptr to the vector data so we skip those
    *reinterpret_cast< uintptr_t * >( allocated + 0x1D21F3 + 6 ) = uintptr_t( &parsed_cfg ) + 4;

    spdlog::info( "Done." );
}

int __stdcall DllMain( HINSTANCE mod, unsigned long reason, void *reserved )
{
    if ( reason == DLL_PROCESS_ATTACH ) {
        auto main_thread = CreateThread( nullptr, 0, LPTHREAD_START_ROUTINE( hooks_main ), reserved, 0, nullptr );

        if ( main_thread )
            CloseHandle( main_thread );
    }

    return 1;
}