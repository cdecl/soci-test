cmake_minimum_required(VERSION 3.11)

project(main)

set(CMAKE_CXX_STANDARD 17)

add_executable(main main.cpp)

target_compile_options(main PRIVATE /MT)
target_include_directories(main PRIVATE D:/Lib/vcpkg/installed/x64-windows-static/include)
target_link_directories(main PRIVATE D:/Lib/vcpkg/installed/x64-windows-static/lib)
target_link_libraries(main PRIVATE libsoci_core_4_0 libsoci_empty_4_0 libsoci_odbc_4_0 odbc32)