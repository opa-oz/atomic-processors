#include <iostream>
#include <fstream>
#include <sstream>

#include <CLI/App.hpp>
#include <nlohmann/json.hpp>

#include "../utils/string.cpp"
#include "../utils/read.cpp"

using namespace std;
using json = nlohmann::json;

namespace Templater
{
  std::string _input_path;
  std::string _variables;
  std::string _variables_file;
  std::string _output_path;

  void process(const string &input_path, const string &variables, const string &output_path)
  {
    auto json_input = json::parse(variables);
    ifstream input(input_path);
    ofstream output;

    output.open(output_path);

    if (input.is_open())
    {
      string line;

      while (getline(input, line))
      {
        for (auto &element : json_input.items())
        {
          string key = "${" + element.key() + "}";
          Utils::String::replace_all(line, key, element.value());
        }
        output << line << endl;
      }

      input.close();
      output.close();
    }
  }

  void init(CLI::App &app)
  {
    auto templater = app.add_subcommand("templater", "Replace variables in text using JSON obj");

    templater->add_option("--input1", _input_path, "Input file")->required()->check(CLI::ExistingFile);
    templater->add_option("--param1", _variables, "Variables JSON object")->required();
    templater->add_option("--output1", _output_path, "Output file")->required();

    templater->callback([&]()
                        { process(_input_path, _variables, _output_path); });

    auto templater_files = app.add_subcommand("templater_f", "Replace variables in text using JSON file");
    templater_files->add_option("--input1", _input_path, "Input file")->required()->check(CLI::ExistingFile);
    templater_files->add_option("--input2", _variables_file, "JSON file with variables object")->required()->check(CLI::ExistingFile);
    templater_files->add_option("--output1", _output_path, "Output file")->required();

    templater_files->callback([&]()
                              { process(_input_path, Utils::Read::file2string(_variables_file), _output_path); });
  };
}
