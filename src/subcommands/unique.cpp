#include <iostream>
#include <list>
#include <vector>
#include <fstream>
#include <unordered_set>

#include "CLI/App.hpp"
#include "nlohmann/json.hpp"

#include "../utils/string.cpp"
#include "../utils/read.cpp"
#include "../utils/write.cpp"
#include "../utils/json.cpp"
#include "../utils/vector.cpp"

using namespace std;
using json = nlohmann::json;

namespace Unique
{

  enum class Filetype : int
  {
    JSON,
    CSV //@todo: maybe one day
  };

  enum class Datatype : int
  {
    Simple,
    Complex
  };

  string _input_path;
  string _output_path;
  string _keys;

  Filetype _filetype{Filetype::JSON};
  Datatype _datatype{Datatype::Simple};
  map<string, Filetype> filetype_map{{"json", Filetype::JSON}, {"csv", Filetype::CSV}};
  map<string, Datatype> datatype_map{{"simple", Datatype::Simple}, {"complex", Datatype::Complex}};

  void process(const string &input_path, const Filetype &filetype, const Datatype &datatype, const string &_keys, const string &output_path)
  {
    vector<string> keys({});

    if (_keys.length() > 0)
    {
      keys = Utils::String::split(_keys);
    }

    using CLI::enums::operator<<;
    cout << "Processing params: " << endl;
    cout << "- filetype=" << filetype << endl;
    cout << "- datatype=" << datatype << endl;
    cout << "- keys=" << Utils::String::join(keys, ", ") << endl;

    if (filetype != Filetype::JSON)
    {
      throw runtime_error("We can only process JSON");
    }

    cout << "Lets parse input file" << endl;
    auto input = Utils::Read::file2json(input_path);

    if (!input.is_array())
    {
      throw runtime_error("Expected json array");
    }

    if (datatype == Datatype::Simple)
    {
      std::unordered_set<size_t> hashes = {};
      json output = json::array();

      for (json::iterator it = input.begin(); it != input.end(); ++it)
      {
        auto value = it.value();
        if (value.is_array() || value.is_object())
        {
          throw runtime_error("Expected FLAT array");
        }

        const size_t h = Utils::JSON::get_hash(value);
        if (hashes.find(h) == hashes.end())
        {
          hashes.insert(h);
          output.push_back(value);
        }
      }

      Utils::Write::json2file(output_path, output);
    }
  }

  void init(CLI::App &app)
  {
    auto unique = app.add_subcommand("unique", "Uniq any array");

    unique->add_option("--input1", _input_path, "Input file")->required()->check(CLI::ExistingFile);
    unique->add_option("--param1", _filetype, "Type of input file (CSV/JSON). Default: JSON")
        ->transform(CLI::CheckedTransformer(filetype_map, CLI::ignore_case));
    unique->add_option("--param2", _datatype, "Data type (Simple/Complex). Default: Simple")
        ->transform(CLI::CheckedTransformer(datatype_map, CLI::ignore_case));
    unique->add_option("--param3", _keys, "Keys to match 'Complex' (string, comma separated). Default: <all>");
    unique->add_option("--output1", _output_path, "Output file")->required();

    unique->callback([&]()
                     { Unique::process(_input_path, _filetype, _datatype, _keys, _output_path); });
  }
}
