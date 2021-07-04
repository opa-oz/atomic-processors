#pragma once

#include <iostream>

using namespace std;

namespace Utils
{
    bool replace(string &str, const string &from, const string &to)
    {
        size_t start_pos = str.find(from);
        if (start_pos == string::npos)
            return false;
        str.replace(start_pos, from.length(), to);
        return true;
    }

    void replace_all(string &str, const string &from, const string &to)
    {
        bool success = Utils::replace(str, from, to);

        while (success)
        {
            success = Utils::replace(str, from, to);
        }
    }
}