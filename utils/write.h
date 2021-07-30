#pragma once

#include <nlohmann/json.hpp>

namespace Utils::Write {
    using namespace std;

    void json2file(const string &filename, const nlohmann::json &obj);
}