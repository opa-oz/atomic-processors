cmake_minimum_required(VERSION 3.19)
project(atomic_processors)

set(CMAKE_CXX_STANDARD 14)
# set(CMAKE_TOOLCHAIN_FILE "/Users/opa_oz/vcpkg/scripts/buildsystems/vcpkg.cmake")

find_package(CLI11 CONFIG REQUIRED)

add_executable(atomic_processors
        src/main.cpp)

target_link_libraries(atomic_processors PRIVATE CLI11::CLI11)