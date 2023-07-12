#ifndef RELOCS_DUMPER_UTILS_HPP
#define RELOCS_DUMPER_UTILS_HPP

#include "includes.hpp"

struct dump_t {
    dump_t( const char *file_path, const char *base );
    ~dump_t( );
    size_t get_rva( size_t &var );

    byte *data;
    size_t base;// base address
    size_t size;// full dump size
};

// just a helper for easier to read code
struct reloc_data_t {
    reloc_data_t( size_t value, size_t rva ) : value( value ), rva( rva ) {}
    reloc_data_t( dump_t &dump, size_t curr_off )
    {
        this->value = *reinterpret_cast< size_t * >( dump.data + curr_off );
        this->rva = dump.get_rva( this->value );
    }

    size_t value;// absolute virtual address
    size_t rva;  // relative virtual address
};

namespace utils
{
    static bool is_inside_module( size_t addr, dump_t &dump )
    {
        return addr >= dump.base && addr <= dump.base + dump.size;
    }

    static byte *load_file_to_memory( const char *file_path, size_t &file_size )
    {
        byte *out;
        std::fstream file( file_path, std::ios::binary | std::ios::in );

        if ( file.fail( ) ) {
            spdlog::error( "failed to open dump {}", file_path );
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
}// namespace utils

// dump_t functionality
dump_t::dump_t( const char *file_path, const char *base )
{
    std::stringstream base_str( base );
    base_str >> std::hex >> this->base;
    this->data = utils::load_file_to_memory( file_path, this->size );
}

dump_t::~dump_t( )
{
    this->base = 0x0;
    this->size = 0x0;
    free( this->data );
}

size_t dump_t::get_rva( size_t &var )
{
    return var - this->base;
}

#endif