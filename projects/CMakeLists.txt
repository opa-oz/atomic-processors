link_libraries(nlohmann_json::nlohmann_json UtilsString UtilsRead UtilsJSON UtilsWrite UtilsVector)

include_directories("${PROJECT_SOURCE_DIR}/incl/")

add_subdirectory(anime-alice)