#pragma once

#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

namespace Utils
{
    namespace JSON
    {
        size_t null_hash = std::hash<std::string>{}("_opa_oz_null");

        size_t get_hash(const json &value)
        {
            if (value.is_string())
            {
                return std::hash<std::string>{}(value.get<std::string>());
            }
            else if (value.is_number())
            {
                return std::hash<double>{}(value.get<double>());
            }
            else if (value.is_boolean())
            {
                return std::hash<bool>{}(value.get<bool>());
            }
            else if (value.is_null())
            {
                return Utils::JSON::null_hash;
            }
            else
            {
                return std::hash<std::string>{}(value.dump());
            }
        }
    }
}