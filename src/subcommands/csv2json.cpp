#include <iostream>
#include <string>
#include <fstream>

#include "CLI/App.hpp"
#include "../../include/csv.hpp"
#include <nlohmann/json.hpp>

#include "../utils/read.cpp"

using namespace std;
using namespace csv;
using json = nlohmann::json;

namespace CSV2JSON
{
    string _input_path;
    string _output_path;

    string _title_mapping_json("{}");
    string _title_mapping_path;

    string _quotechar(1, '"');
    string _delimiter(";");

    void write_row(ofstream &output, const CSVRow &row, const bool &is_mapping_empty, json &mapping)
    {
        json new_el = json({});
        json row_parsed = json::parse(row.to_json());

        if (is_mapping_empty)
        {
            for (auto &element : row_parsed.items())
            {
                if (element.value() != "")
                {
                    new_el[element.key()] = element.value();
                }
            }
        }
        else
        {
            for (auto &element : row_parsed.items())
            {
                if (mapping.contains(element.key()))
                {
                    string new_key = mapping.at(element.key());
                    new_el[new_key] = element.value();
                }
                else if (element.value() != "")
                {
                    new_el[element.key()] = element.value();
                }
            }
        }

        output << new_el.dump();
    }

    void process(string &input_path, const string &title_mapping_json, const string &delimiter, const string &quotechar, string &output_path)
    {
        cout << "Delimiter: " << delimiter << endl;
        cout << "Quotechar: " << quotechar << endl;
        cout << "Mapping: " << title_mapping_json << endl;

        CSVFormat format;
        format.delimiter(delimiter[0])
            .quote(quotechar[0]);

        CSVReader reader(input_path, format);
        CSVRow row;

        json mapping = json::parse(title_mapping_json);
        bool is_mapping_empty = mapping.empty();

        if (output_path.length() < 1)
        {
            throw runtime_error("There is no output file");
        }

        ofstream output;

        output.open(output_path);
        output << "[";

        reader.read_row(row);
        bool is_first_row = true;

        do
        {
            if (!is_first_row)
            {
                output << ",";
            }
            else
            {
                is_first_row = false;
            }

            write_row(output, row, is_mapping_empty, mapping);
        } while (reader.read_row(row));

        output
            << "]" << endl;
        output.close();
    }

    void init(CLI::App &app)
    {
        auto csv2json = app.add_subcommand("csv2json", "Convert CSV to JSON");

        csv2json->add_option("--input1", _input_path, "Input file")->required()->check(CLI::ExistingFile);
        csv2json->add_option("--output1", _output_path, "Output file")->required();

        csv2json->add_option("--param1", _title_mapping_json, "Header mapping object. Default: '{}'");
        csv2json->add_option("--param2", _delimiter, "Delimiter char. Default: ';'");
        csv2json->add_option("--param3", _quotechar, "Quoting char. Default '\"'");

        csv2json->callback([&]()
                           { process(_input_path, _title_mapping_json, _delimiter, _quotechar, _output_path); });

        auto csv2json_f = app.add_subcommand("csv2json_f", "Convert CSV to JSON with file mapping");

        csv2json_f->add_option("--input1", _input_path, "Input file")->required()->check(CLI::ExistingFile);
        csv2json_f->add_option("--input2", _title_mapping_path, "File with header mapping object.")->required()->check(CLI::ExistingFile);
        csv2json_f->add_option("--output1", _output_path, "Output file")->required();

        csv2json_f->add_option("--param2", _delimiter, "Delimiter char. Default: ';'");
        csv2json_f->add_option("--param3", _quotechar, "Quoting char. Default '\"'");

        csv2json_f->callback([&]()
                             { CSV2JSON::process(_input_path, Utils::Read::file2string(_title_mapping_path), _delimiter, _quotechar, _output_path); });
    }
}