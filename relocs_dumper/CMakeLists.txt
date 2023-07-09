cmake_minimum_required(VERSION 3.22)
project(relocs_dumper)
set(CMAKE_CXX_STANDARD 23)

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

add_executable(${PROJECT_NAME} ${SRC})
find_library(SPDLOG_LIBRARY spdlog.lib PATHS "${CMAKE_CURRENT_SOURCE_DIR}/deps/spdlog")

target_link_libraries(${PROJECT_NAME} PRIVATE ${SPDLOG_LIBRARY})
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/deps")