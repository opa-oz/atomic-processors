#pragma once

#include <string>
#include "../incl/CLI11.hpp"

namespace AtomicProcessors::Templater {
    using namespace std;

    namespace {
        std::string _input_path;
        std::string _variables;
        std::string _variables_file;
        std::string _output_path;
    }

    void process(const string &input_path, const string &variables, const string &output_path);

    void init(CLI::App &app);
}