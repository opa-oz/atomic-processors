#pragma once

#include <vector>
#include <string>

namespace Utils::String {
    using namespace std;

    bool replace(string &str, const string &from, const string &to);

    void replace_all(string &str, const string &from, const string &to);

    void to_lower(string &str);

    string to_lower_copy(const string &str);

    vector<std::string> split(const std::string &str, const char &delimiter = ',');

    string join(const vector<string> &strings, const string &delimiter);
}