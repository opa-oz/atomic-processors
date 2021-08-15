#include "iostream"
#include "json.h"

using namespace std;
using json = nlohmann::json;

namespace Utils::JSON {
    namespace {
        size_t null_hash = std::hash<std::string>{}("_opa_oz_null");
    }

    size_t get_hash(const json &value) {
        if (value.is_string()) {
            return std::hash<std::string>{}(value.get<std::string>());
        } else if (value.is_number()) {
            return std::hash<double>{}(value.get<double>());
        } else if (value.is_boolean()) {
            return std::hash<bool>{}(value.get<bool>());
        } else if (value.is_null()) {
            return Utils::JSON::null_hash;
        } else {
            return std::hash<std::string>{}(value.dump());
        }
    }

    void hash_combine(size_t &seed, const size_t &val) {
        seed ^= val + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }

    size_t get_hash_by_keys(const json &value, const vector<string> &keys) {
        size_t seed = 0;

        for (const auto &key : keys) {
            if (value.contains(key)) {
                hash_combine(seed, get_hash(value[key]));
            }
        }

        return seed;
    }

    void copy(const json &value, json &target, const string &key) {
        if (value.is_string()) {
            target[key] = value.get<std::string>();
        } else if (value.is_number()) {
            if (value.is_number_float()) {
                target[key] = value.get<double>();
            } else {
                target[key] = value.get<int>();
            }
        } else if (value.is_boolean()) {
            target[key] = value.get<bool>();
        } else if (value.is_null()) {
            target[key] = nullptr;
        } else {
            target[key] = value.dump();
        }
    }

    void push_to(const json &value, json &target) {
        if (value.is_string()) {
            target.push_back(value.get<std::string>());
        } else if (value.is_number()) {
            if (value.is_number_float()) {
                target.push_back(value.get<double>());
            } else {
                target.push_back(value.get<int>());
                cout << target << endl;
                cout << value << endl;
            }
        } else if (value.is_boolean()) {
            target.push_back(value.get<bool>());
        } else if (value.is_null()) {
            target.push_back(nullptr);
        } else {
            target.push_back(value.dump());
        }
    }
}
