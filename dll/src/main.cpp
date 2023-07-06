#include "includes.hpp"

std::mutex g_mutex;

SafetyHookInline g_connect_hk{ };
SafetyHookInline g_config_handler_hk{ };
SafetyHookInline g_curl_easy_setopt_hk{ };

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

SafetyHookInline g_read_packet_hk{ };
SafetyHookInline g_send_packet_hk{ };

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

void update_config_list( )
{
    char a1[] = "its shoutout time";
    char a2[] = "to big black";
    char a3[] = "nigga balls";

    reinterpret_cast< int( __thiscall * )( void *, char * ) >( 0x19BA5480 )( reinterpret_cast< void * >( 0x1A09A770 ), a1 );
    reinterpret_cast< int( __thiscall * )( void *, char * ) >( 0x19BA5480 )( reinterpret_cast< void * >( 0x1A09A770 ), a2 );
    reinterpret_cast< int( __thiscall * )( void *, char * ) >( 0x19BA5480 )( reinterpret_cast< void * >( 0x1A09A770 ), a3 );

    //bool new_configs = reinterpret_cast< bool( __cdecl * )( ) >( 0x19CF27C0 )( );

    //if ( new_configs ) {
    //    new_configs = *reinterpret_cast< bool * >( reinterpret_cast< void * >( 0x1A235F9F ) );
    //}

    //   if ( !*reinterpret_cast< bool * >( reinterpret_cast< void * >( 0x1A235F9F ) ) ) {
    //        for ( int j = 0;; ++j ) {
    //            result = sub_19BA5E00( &unk_1A09A8D0 );
    //            if ( j >= result )
    //                break;
    //            if ( reinterpret_cast< char* >( reinterpret_cast< void * >( 0x1A235F9C ) )[ j ] ) {
    //                sub_19B98970( ( char * ) v85 );
    //                v85[ 0 ] = 10;
    //                v28 = ( const void * ) sub_19BA2DF0( j );
    //                memmove( v86, v28, 0x25u );

    //                reinterpret_cast< int( __thiscall * )( void *, char * ) >( 0x19BA5480 )( reinterpret_cast< void * >( 0x1A09A770 ), v85 ); // push_back
    //                sub_19B9C7F0( v85 );
    //                sub_19B9AA40( v85 );
    //            }
    //        }
    //        *reinterpret_cast< bool * >( reinterpret_cast< void * >( 0x1A235F9F ) ) = true;
    //}

    auto v1 = reinterpret_cast< int( __thiscall * )( void * ) >( 0x19BA5EA0 )( reinterpret_cast< void * >( 0x1A09A770 ) );

    for ( int i = 0; i < v1; ++i ) {
        const char* v82 = reinterpret_cast< const char*( __thiscall * )( void *, unsigned int ) >( 0x19BA2E50 )( reinterpret_cast< void * >( 0x1A09A770 ), i );

        spdlog::info( "{}", v82 );
    }
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

    reinterpret_cast< void( __cdecl * )( ) >( 0x19E358D5 )( );// security init cookie
    reinterpret_cast< int( __cdecl * )( HINSTANCE, DWORD, LPVOID ) >( 0x19E34E64 )( reinterpret_cast< HINSTANCE >( 0x19B30000 ), DLL_PROCESS_ATTACH, 0 );

    reinterpret_cast< void *( __thiscall * ) ( void * ) >( 0x19B93E40 )( reinterpret_cast< void * >( 0x1A09A770 ) );
    update_config_list( );

    spdlog::info( "Done." );

    //void *__thiscall sub_19B93E40(void *this)

    //while ( !vector_address )
    //    std::this_thread::sleep_for( std::chrono::milliseconds( 400 ) );

    //sub_19B98970( ( char * ) v307 );
    //v307[ 0 ] = 8;
    //memmove( v308, &byte_1A28E1A4, 0x11u );
    //v308[ 61 ] = 0;
    //v309 = dword_1A28E130;
    //vector_push_back( g_cfg_vector, ( int ) v307 );
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