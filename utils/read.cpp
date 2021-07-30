#include <fstream>
#include <sstream>

#include "read.h"


namespace Utils::Read {
    using namespace std;

    string file2string(const string &filename) {
        ifstream input(filename);
        stringstream buffer;
        buffer << input.rdbuf();

        string result = buffer.str();

        return result;
    }

    nlohmann::json file2json(const string &filename) {
        return nlohmann::json::parse(Utils::Read::file2string(filename));
    }
}
