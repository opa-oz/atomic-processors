#pragma once

#include <vector>
#include <string>
#include <algorithm>

namespace Utils::String {
    using namespace std;

    const string WHITESPACE = " \n\r\t\f\v";

    bool replace(string &str, const string &from, const string &to);

    void replace_all(string &str, const string &from, const string &to);

    void to_lower(string &str);

    string to_lower_copy(const string &str);

    vector<string> split(const string &str, const char &delimiter = ',');

    string join(const vector<string> &strings, const string &delimiter);

    string ltrim(const string &s);

    string rtrim(const string &s);

    string trim(const string &s);

    size_t get_hash(const string &s);
}