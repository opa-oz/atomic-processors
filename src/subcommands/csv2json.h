#pragma once

#include <iostream>
#include <string>
#include <fstream>

#include "CLI/App.hpp"
#include "../../include/csv.hpp"
#include <nlohmann/json.hpp>

using namespace csv;
using json = nlohmann::json;
using namespace std;

namespace CSV2JSON
{
  string _input_path;
  string _output_path;

  string _title_mapping_json("{}");
  string _title_mapping_path;

  string _quotechar(1, '"');
  string _delimiter(";");

  void write_row(ofstream &output, const CSVRow &row, const bool &is_mapping_empty, json &mapping);

  void process(string &input_path, const string &title_mapping_json, const string &delimiter, const string &quotechar, string &output_path);

  void init(CLI::App &app);

}
