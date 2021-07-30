#pragma once

#include <string>
#include <nlohmann/json.hpp>

namespace Utils::Read {
    using namespace std;

    string file2string(const string &filename);

    nlohmann::json file2json(const string &filename);
}