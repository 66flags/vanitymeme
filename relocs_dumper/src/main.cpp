#include "includes.hpp"

byte *load_file_to_memory( const char *file_path, size_t &file_size )
{
    byte * out;
    std::fstream file( file_path, std::ios::binary | std::ios::in );

    if ( file.fail( ) ) {
        spdlog::error( "failed to open dump" );
        return 0;
    }

    file.seekg( 0, std::ios::end );
    size_t size = file.tellg( );

    file.seekg( 0, std::ios::beg );

    out = ( byte * ) malloc( size );
    file.read( ( char * ) out, size );

    file.close( );

    file_size = size;

    return out;
}

int main( int argc, char *argv[] )
{
    // init variables
    const char *dump_path1 = argv[ 1 ];
    const char *dump_base1 = argv[ 2 ];
    const char *dump_path2 = argv[ 3 ];
    const char *dump_base2 = argv[ 4 ];

    std::fstream out_file{ };

    if ( !dump_path1 || !dump_base1 || !dump_path2 || !dump_base2 ) {
        spdlog::error( "usage: relocs_dumper <dump_path1> <dump_base1> <dump_path2> <dump_base2>" );
        return 0;
    }

    size_t dump1_size{ };
    size_t dump2_size{ };
    auto dump1 = load_file_to_memory( dump_path1, dump1_size );
    auto dump2 = load_file_to_memory( dump_path2, dump2_size );

    if ( !dump1 || !dump2 )
        return 0;

    out_file.open( "relocs.hpp", std::ios::out | std::ios::trunc );

    if ( out_file.fail( ) ) {
        spdlog::error( "failed to open output file" );
        return 0;
    }

    if ( dump1_size != dump2_size ) {
        spdlog::error( "files are not the same size" );
        return 0;
    }

    std::vector< std::tuple< size_t, size_t > > reloc_data;
    std::stringstream out_str;

    size_t dump1_base{ };
    size_t dump2_base{ };

    std::stringstream base1( dump_base1 ), base2( dump_base2 );
    base1 >> std::hex >> dump1_base;
    base2 >> std::hex >> dump2_base;

    reloc_data.reserve( dump1_size );

    spdlog::info( "finding relocs..." );

    auto is_inside_module = [ & ]( size_t addr, size_t base ) -> bool {
        return addr >= base && addr <= base + dump1_size;
    };

    // iterate thru bytes
    size_t curr_offset{ };
    size_t end{ dump1_size - sizeof( size_t ) };
    while ( curr_offset < end ) {// skip the first byte, we literally don't care about it
        // out data
        size_t dump1_val = *reinterpret_cast< size_t * >( dump1 + curr_offset );
        size_t dump2_val = *reinterpret_cast< size_t * >( dump2 + curr_offset );
        size_t dump1_rva = dump1_val - dump1_base;
        size_t dump2_rva = dump2_val - dump2_base;

        if ( !is_inside_module( dump1_val, dump1_base ) || dump1_val == dump2_val || !is_inside_module( dump2_val, dump2_base ) || dump1_rva != dump2_rva ) {
            // skip this byte
            curr_offset++;
            continue;
        }

        // push reloc data
        reloc_data.push_back( std::make_tuple( curr_offset, dump1_rva ) );

        // skip current rva
        curr_offset += sizeof( size_t );
    }

    // setup format
    out_str << "#ifndef LDR_RELOCATIONS_HPP\n"
            << "#define LDR_RELOCATIONS_HPP\n"
            << "\n"
            << "std::vector< std::tuple< size_t, size_t > > reloc_data = {";

    // add relocs from list
    for ( size_t i = 0; i < reloc_data.size( ); i++ ) {
        bool is_end = i == reloc_data.size( ) - 1;
        size_t reloc_offset = std::get< 0 >( reloc_data[ i ] );
        size_t reloc_rva = std::get< 1 >( reloc_data[ i ] );

        out_str << " { 0x" << std::hex << std::uppercase << reloc_offset << ", 0x" << reloc_rva << " }" << ( is_end ? " " : "," );
    }

    // end format
    out_str << "};\n"
            << "\n"
            << "#endif // LDR_RELOCATIONS_HPP";

    out_file << out_str.str( ); // write to file

    out_file.close( );
    free( dump1 );
    free( dump2 );

    spdlog::info( "done, found {} relocs", reloc_data.size( ) );

    return 1;
}