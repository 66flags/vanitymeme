cmake_minimum_required(VERSION 3.22)
project(vanitycheats)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_USE_WIN32_THREADS_INIT ON)
set(CMAKE_USE_WIN32_WINNT ON)

add_compile_definitions(ZYDIS_STATIC_DEFINE)
add_compile_definitions(ZYCORE_STATIC_DEFINE)

file(GLOB_RECURSE SRC
        # source
        "src/*.*" ,
        "src/**/*.cpp" ,
        "src/**/*.*" ,

        # deps
        "deps/*.*" ,
        "deps/**/*.cpp" ,
        "deps/**/*.*" ,
        )

add_library(${PROJECT_NAME} MODULE ${SRC})
find_library(SPDLOG_LIBRARY spdlog PATHS "${CMAKE_CURRENT_SOURCE_DIR}/deps/spdlog")
find_library(D3D9_LIBRARY d3d9.lib PATHS "$ENV{DXSDK_DIR}/Lib/x86")
find_library(D3DX9_LIBRARY d3dx9.lib PATHS "$ENV{DXSDK_DIR}/Lib/x86")
target_link_libraries(${PROJECT_NAME} PRIVATE ${SPDLOG_LIBRARY} ${D3D9_LIBRARY} ${D3DX9_LIBRARY} ws2_32 wsock32)
link_directories("$ENV{DXSDK_DIR}/Lib/x86")
include_directories("$ENV{DXSDK_DIR}/Include")
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/deps")