link_libraries(nlohmann_json::nlohmann_json UtilsString UtilsRead UtilsJSON UtilsWrite UtilsVector FileType)

include_directories("${PROJECT_SOURCE_DIR}/incl/")

add_library(Templater templater.cpp)
add_library(CSV2JSON csv2json.cpp)
add_library(Unique unique.cpp)
add_library(Pick pick.cpp)
add_library(TextCleanUp text_clean.cpp)