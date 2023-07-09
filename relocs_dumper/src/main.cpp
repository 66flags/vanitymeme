#include "includes.hpp"

int main( int argc, char *argv[] )
{
    // init variables
    const char *dump_path1 = argv[ 1 ];
    const char *dump_path2 = argv[ 2 ];

    std::fstream dump1{ }, dump2{ }, out_file{ };

    if ( !dump_path1 || !dump_path2 ) {
        spdlog::error( "usage: relocs_dumper <dump_path1> <dump_path2>" );
        return 0;
    }

    dump1.open( dump_path1, std::ios::binary | std::ios::in );
    dump2.open( dump_path2, std::ios::binary | std::ios::in );
    out_file.open( "relocs.hpp", std::ios::out | std::ios::trunc );

    if ( dump1.fail( ) ) {
        spdlog::error( "failed to open dump 1" );
        return 0;
    } else if ( dump2.fail( ) ) {
        spdlog::error( "failed to open dump 2" );
        return 0;
    } else if ( out_file.fail( ) ) {
        spdlog::error( "failed to open output file" );
        return 0;
    }

    // check if both files have the same size
    std::filesystem::path pdump1( dump_path1 ), pdump2( dump_path2 );
    if ( std::filesystem::file_size( pdump1 ) != std::filesystem::file_size( pdump2 ) ) {
        spdlog::error( "files are not the same size" );
        return 0;
    }

    std::istreambuf_iterator< char > dump1_it( dump1 ), dump2_it( dump2 ), end;
    std::vector< size_t > reloc_data;
    std::stringstream out_str;

    reloc_data.reserve( size_t(25) << 20 ); // reserve 25MB so we don't do extra allocs lel

    spdlog::info( "finding relocs..." );

    // iterate thru bytes
    for ( size_t curr_off{ 0x0 }; dump1_it != end && dump2_it != end; ++dump1_it, ++dump2_it, curr_off++ ) {
        if ( *dump1_it != *dump2_it )
            reloc_data.push_back( curr_off );
    }

    // alr used these
    dump1.close( );
    dump2.close( );

    // setup format
    out_str << "#pragma once\n"
            << "\n"
            << "std::array< size_t, " << reloc_data.size( ) << " > relocations = {";

    // add relocs from list
    for ( size_t i = 0; i < reloc_data.size( ); i++ ) {
        bool is_end = i == reloc_data.size( ) - 1;
        out_str << " 0x" << std::hex << std::uppercase << reloc_data.at( i ) << ( is_end ? " " : "," );
    }

    // end format
    out_str << "};";

    // why not LOL
    out_str << R"(
static void fix_relocations(size_t dump1_base, size_t dump2_base) {
    size_t delta = dump1_base - dump2_base;

    for ( size_t i = 0; i < relocations.size( ); i++ )
        *reinterpret_cast<size_t*>( delta + relocations.at( i ) ) += delta;
})";

    out_file << out_str.str( ); // write to file

    out_file.close( );

    spdlog::info( "done, found {} relocs", reloc_data.size( ) );

    return 1;
}