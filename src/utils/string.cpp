#pragma once

#include <iostream>
#include <algorithm>
#include <cctype>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

namespace Utils
{
    namespace String
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
            bool success = Utils::String::replace(str, from, to);

            while (success)
            {
                success = Utils::String::replace(str, from, to);
            }
        }

        void to_lower(string &str)
        {
            transform(str.begin(), str.end(), str.begin(),
                      [](unsigned char c)
                      { return tolower(c); });
        }

        string to_lower_copy(const string &str)
        {
            string newString = str;

            to_lower(newString);
            return newString;
        }

        vector<std::string> split(const std::string &str, const char &delimiter = ',')
        {
            stringstream ss(str);
            vector<string> result;

            while (ss.good())
            {
                string substr;
                getline(ss, substr, delimiter);
                result.push_back(substr);
            }

            return result;
        }

        string join(const vector<string> &strings, const string &delimiter)
        {
            size_t total = 0;
            size_t count = 0;

            for (auto s : strings)
                total += s.size();

            string all;

            all.reserve(total + 1);
            for (auto s : strings)
            {
                count++;
                all.append(s);

                if (count != strings.size())
                {
                    all.append(delimiter);
                }
            }

            return all;
        }
    }
}