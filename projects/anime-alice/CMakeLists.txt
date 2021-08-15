link_libraries(nlohmann_json::nlohmann_json UtilsString UtilsRead UtilsJSON UtilsWrite UtilsVector FileType)

include_directories("${PROJECT_SOURCE_DIR}/incl/")

add_library(ExtractLogs extract.cpp)