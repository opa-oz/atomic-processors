#pragma once

#include <fstream>
#include <sstream>

#include <nlohmann/json.hpp>

using namespace std;

namespace Utils
{
    std::string file2string(const string &filename)
    {
        ifstream input(filename);
        stringstream buffer;
        buffer << input.rdbuf();

        string result = buffer.str();

        return result;
    }

    nlohmann::json file2json(const string &filename)
    {
        return nlohmann::json::parse(Utils::file2string(filename));
    }
}