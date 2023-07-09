#ifndef LMAOBOX_LDR_INCLUDES_HPP
#define LMAOBOX_LDR_INCLUDES_HPP

#include <windows.h>
#include <cstdint>
#include <vector>
#include <deque>
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
#include "relocations.hpp"

// extra sizing and extra pads for struct alignment
struct config_data_t {
    char loaded_config[ 37 ];
    char config_name[ 33 ];
    char owner_name[ 26 ];
    bool unk_bool;
    char gap61[ 1 ];
    bool is_public;
    bool is_user_config; // whether or not this goes in the browser or our downloaded configs
    bool should_delete;
    bool is_liked;
    int user_id;
    int rating;
    int downloads;
    int category;
    int server_response_code; // used in config_handler() (completely useless)
    int pad;
    int64_t creation_date;
};
static_assert( sizeof( config_data_t ) == 0x88 );

#endif//LMAOBOX_LDR_INCLUDES_HPP
