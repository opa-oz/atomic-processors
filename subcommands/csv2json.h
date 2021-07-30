#pragma once

#include <string>
#include <fstream>
#include <nlohmann/json.hpp>
#include "../incl/csv.hpp"
#include "../incl/CLI11.hpp"

namespace AtomicProcessors::CSV2JSON {
    using namespace std;
    using namespace csv;
    using json = nlohmann::json;

    namespace {
        string _input_path;
        string _output_path;

        string _title_mapping_json("{}");
        string _title_mapping_path;

        string _quotechar(1, '"');
        string _delimiter(";");
    }

    void write_row(ofstream &output, const CSVRow &row, const bool &is_mapping_empty, json &mapping);

    void process(string &input_path, const string &title_mapping_json, const string &delimiter, const string &quotechar,
                 string &output_path);

    void init(CLI::App &app);
}