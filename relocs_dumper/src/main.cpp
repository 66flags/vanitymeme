#include "util.hpp"

int main( int argc, char *argv[] )
{
    // init variables
    const char *dump_path1 = argv[ 1 ];
    const char *dump_base1 = argv[ 2 ];
    const char *dump_path2 = argv[ 3 ];
    const char *dump_base2 = argv[ 4 ];


    if ( !dump_path1 || !dump_base1 || !dump_path2 || !dump_base2 ) {
        spdlog::error( "usage: relocs_dumper <dump_path1> <dump_base1> <dump_path2> <dump_base2>" );
        return 0;
    }

    // out data
    std::vector< reloc_data_t > reloc_data{ };
    std::stringstream out_str{ };
    std::fstream out_file{ };

    auto dump1 = dump_t( dump_path1, dump_base1 );
    auto dump2 = dump_t( dump_path2, dump_base2 );

    if ( !dump1.data || !dump2.data )
        return 0;

    if ( dump1.size != dump2.size ) {
        spdlog::error( "files are not the same size" );
        return 0;
    }

    // reserve data for comparison so we don't do extra allocations
    reloc_data.reserve( dump1.size );

    out_file.open( "relocs.hpp", std::ios::out | std::ios::trunc );

    if ( out_file.fail( ) ) {
        spdlog::error( "failed to open output file" );
        return 0;
    }

    spdlog::info( "finding relocs..." );

    // iterate thru bytes
    size_t curr_offset{ };
    size_t end{ dump1.size - sizeof( size_t ) };
    while ( curr_offset < end ) {
        auto reloc1 = reloc_data_t( dump1, curr_offset );
        auto reloc2 = reloc_data_t( dump2, curr_offset );

        bool is_hard_address = reloc1.value == reloc2.value;// hardcoded address, always the same
        bool is_relative_call = reloc1.rva != reloc2.rva;   // this is a relative call, don't relocate

        // data outside of range
        if ( !utils::is_inside_module( reloc1.value, dump1 ) || !utils::is_inside_module( reloc2.value, dump2 ) ) {
            curr_offset++;
            continue;
        }

        if ( is_hard_address || is_relative_call ) {
            curr_offset++;
            continue;
        }

        // push reloc data
        reloc_data.push_back( { curr_offset, reloc1.rva } );

        // skip current reloc
        curr_offset += sizeof( size_t );
    }

    // setup format for offsets list
    out_str << "#ifndef LDR_RELOCATIONS_HPP\n"
            << "#define LDR_RELOCATIONS_HPP\n"
            << "\n"
            << "std::array< size_t, 0x" << std::hex << std::uppercase << reloc_data.size( ) << " > reloc_off = {";

    // offsets list
    for ( size_t i = 0; i < reloc_data.size( ); i++ ) {
        bool is_end = i == reloc_data.size( ) - 1;

        out_str << " 0x" << reloc_data[ i ].value << ( is_end ? " " : "," );
    }

    // setup format for rva list
    out_str << "};\n"
            << "\n"
            << "std::array< size_t, 0x" << reloc_data.size( ) << " > reloc_rva = {";

    // rva list
    for ( size_t i = 0; i < reloc_data.size( ); i++ ) {
        bool is_end = i == reloc_data.size( ) - 1;

        out_str << " 0x" << reloc_data[ i ].rva << ( is_end ? " " : "," );
    }

    // end format
    out_str << "};\n"
            << "\n"
            << "#endif // LDR_RELOCATIONS_HPP";

    out_file << out_str.str( );// write to file

    out_file.close( );

    spdlog::info( "done, found {} relocs", reloc_data.size( ) );

    return 1;
}