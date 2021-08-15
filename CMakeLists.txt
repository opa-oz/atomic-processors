cmake_minimum_required(VERSION 3.18.4)
project(AtomicProcessors VERSION 1.0)

include(FetchContent)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

configure_file(config.h.in config.h)

FetchContent_Declare(json
        GIT_REPOSITORY https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent
        GIT_TAG v3.7.3)

FetchContent_GetProperties(json)
if (NOT json_POPULATED)
    FetchContent_Populate(json)
    add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif ()

include_directories("${PROJECT_SOURCE_DIR}/incl/")

add_subdirectory(utils)
add_subdirectory(subcommands)
add_subdirectory(projects)

add_executable(AtomicProcessors main.cpp)
target_link_libraries(AtomicProcessors
        PRIVATE nlohmann_json::nlohmann_json
        PUBLIC UtilsString UtilsRead UtilsVector UtilsJSON UtilsWrite
        Templater CSV2JSON Unique Pick TextCleanUp
        ExtractLogs)

target_include_directories(AtomicProcessors PUBLIC
        "${PROJECT_BINARY_DIR}")