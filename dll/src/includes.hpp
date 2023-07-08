#ifndef LMAOBOX_LDR_INCLUDES_HPP
#define LMAOBOX_LDR_INCLUDES_HPP

#include <windows.h>
#include <cstdint>
#include <vector>
#include <cstdio>
#include <tuple>
#include <utility>
#include <chrono>
#include <thread>
#include <mutex>
#include <d3d9.h>
#include <d3dx9.h>

#include <spdlog/spdlog.h>
#include <safetyhook/safetyhook.hpp>
#include "binary.hpp"
#include "import_list.hpp"

struct config_data_t {
    char type;
    char gap1[ 36 ];
    char owner_name;
    char gap26[ 32 ];
    char config_name;
    char gap47[ 27 ];
    bool is_public;
    char gap63[ 2 ];
    char byte65;
    DWORD user_id;
    DWORD dword6C;
    const char *pchar70;
    int category;
    char gap78[ 16 ];
};
static_assert( sizeof( config_data_t ) == 0x88 );

#endif//LMAOBOX_LDR_INCLUDES_HPP
