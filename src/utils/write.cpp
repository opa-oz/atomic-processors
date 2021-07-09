#pragma once

#include <fstream>
#include <sstream>

#include <nlohmann/json.hpp>

using namespace std;

namespace Utils
{
    namespace Write
    {
        void json2file(const string &filename, const nlohmann::json &obj)
        {
            if (filename.length() < 1)
            {
                throw runtime_error("There is no output file");
            }

            ofstream output;
            output.open(filename);

            output << obj.dump();
            output.close();
        }
    }
}