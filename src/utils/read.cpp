#pragma once

#include <fstream>
#include <sstream>

using namespace std;

namespace Utils
{
    std::string file2string(string &filename)
    {
        ifstream input(filename);
        stringstream buffer;
        buffer << input.rdbuf();

        string result = buffer.str();

        return result;
    }
}