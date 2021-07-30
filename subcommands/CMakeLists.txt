link_libraries(nlohmann_json::nlohmann_json UtilsString UtilsRead UtilsJSON UtilsWrite UtilsVector)

include_directories("${PROJECT_SOURCE_DIR}/incl/")

add_library(Templater templater.cpp)
add_library(CSV2JSON csv2json.cpp)
add_library(Unique unique.cpp)