#pragma once

#include <nlohmann/json.hpp>
#include <vector>

using namespace std;
using json = nlohmann::json;

namespace Utils::JSON {
    size_t get_hash(const json &value);

    void hash_combine(size_t &seed, const size_t &val);

    size_t get_hash_by_keys(const json &value, const vector<string> &keys);
}