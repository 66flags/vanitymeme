#include "includes.hpp"

SafetyHookInline g_connect_hk{ };
SafetyHookInline g_config_handler_hk{ };
SafetyHookInline g_curl_easy_setopt_hk{ };
SafetyHookInline g_read_packet_hk{ };
SafetyHookInline g_send_packet_hk{ };
SafetyHookInline g_checkbox_hk{ };

char lol[ 20 ];
bool __cdecl checkbox_hk( const char *label, bool *v )
{
    // wanted ret 0x19CFBB70
    // checkbox add 0x19D25690
    // inputtext 0x19CA6DC0

    bool result = g_checkbox_hk.call< bool >( label, v );

    // in misc
    if ( reinterpret_cast< uintptr_t >( _ReturnAddress( ) ) == 0x19CFBB70 ) {
        static auto input_text = reinterpret_cast< int( __cdecl * )( void *icon, const char *label, char *buf, int buf_size, int flags, int callback, void *userdata ) >( 0x19CA6DC0 );

        if (input_text(reinterpret_cast<void*>(0x19FE0288), "Menu username", lol, sizeof(lol), 0, 0, 0))
            memmove( reinterpret_cast< void * >( 0x1A27AA44 ), lol, sizeof( lol ) );
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

void __stdcall hooks_main( )
{
    FILE *stream = nullptr;

    AllocConsole( );
    freopen_s( &stream, "CONOUT$", "w", stdout );

    while ( !GetModuleHandleA( "serverbrowser.dll" ) )
        std::this_thread::sleep_for( std::chrono::milliseconds( 400 ) );

    MEMORY_BASIC_INFORMATION mbi;

    if ( !VirtualQuery( reinterpret_cast< void * >( 0x19B30000 ), &mbi, sizeof( mbi ) ) ) {
        spdlog::error( "Failed to find allocated region." );
        return;
    }

    spdlog::info( "Loading binary to memory..." );

    memcpy( reinterpret_cast< void * >( 0x19B30000 ), vanity_bin, sizeof( vanity_bin ) );

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

        *reinterpret_cast< uint32_t * >( std::get< 0 >( _import ) ) = ( uint32_t ) export_proc;
    }

    spdlog::info( "Patching calls..." );

    memset( reinterpret_cast< void * >( 0x19CEEF15 ), 0x90, 5 );
    memset( reinterpret_cast< void * >( 0x19B890F6 ), 0x90, 5 );
    memset( reinterpret_cast< void * >( 0x19C2E3C3 ), 0x90, 5 );
    memset( reinterpret_cast< void * >( 0x19C34030 ), 0x90, 5 );
    memset( reinterpret_cast< void * >( 0x19B8912C ), 0x90, 5 );

    memset( reinterpret_cast< void * >( 0x19D0047F ), 0x90, 5 );
    memset( reinterpret_cast< void * >( 0x19D004EB ), 0x90, 5 );
    memset( reinterpret_cast< void * >( 0x19D005F6 ), 0x90, 5 );
    memset( reinterpret_cast< void * >( 0x19D003AA ), 0x90, 5 );
    // memset( reinterpret_cast< void * >( 0x19B891C1 ), 0x90, 59 );

    *reinterpret_cast< int * >( 0x1A09A5E8 ) = 1337;

    g_send_packet_hk = safetyhook::create_inline( reinterpret_cast< void * >( 0x19BA6CE0 ), reinterpret_cast< void * >( send_packet ) );
    g_read_packet_hk = safetyhook::create_inline( reinterpret_cast< void * >( 0x19BA6D40 ), reinterpret_cast< void * >( read_packet ) );
    g_connect_hk = safetyhook::create_inline( reinterpret_cast< void * >( 0x19BA6B00 ), reinterpret_cast< void * >( connect_hk ) );

    g_curl_easy_setopt_hk = safetyhook::create_inline( reinterpret_cast< void * >( 0x19DA8F40 ), reinterpret_cast< void * >( curl_easy_setopt ) );
    g_config_handler_hk = safetyhook::create_inline( reinterpret_cast< void * >( 0x19C44170 ), reinterpret_cast< void * >( config_handler ) );
    g_checkbox_hk = safetyhook::create_inline( reinterpret_cast< void * >( 0x19D25690 ), reinterpret_cast< void * >( checkbox_hk ) );

    reinterpret_cast< void( __cdecl * )( ) >( 0x19E358D5 )( );// security init cookie
    reinterpret_cast< int( __cdecl * )( HINSTANCE, DWORD, LPVOID ) >( 0x19E34E64 )( reinterpret_cast< HINSTANCE >( 0x19B30000 ), DLL_PROCESS_ATTACH, 0 );

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
    *reinterpret_cast< uintptr_t * >( 0x19D021F3 + 6 ) = uintptr_t( &parsed_cfg ) + 4;

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