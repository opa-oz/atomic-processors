#include <iostream>
#include <nlohmann/json.hpp>
#include "extract.h"

using json = nlohmann::json;

namespace AtomicProcessors::AnimeAlice {
    void ExtractLogs::process(const string &input_path, const Filetype &filetype, const OutputType &output_type,
                              const string &output_path) {
        ifstream input(input_path);
        ofstream output;
        output.open(output_path);

        if (input.is_open()) {
            string line;

            if (filetype == Filetype::JSON) {
                output << '[';
            }

            bool not_empty = false;

            while (getline(input, line)) {
                if (line.find('{') == std::string::npos) {
                    continue;
                }

                auto object = json::parse(line);
                string type = object["message"]["type"];

                if (output_type == OutputType::MIXED
                    || (output_type == OutputType::REQUEST && type == InputMessage)
                    || (output_type == OutputType::RESPONSE && type == OutputMessage)) {
                    if (not_empty) {
                        output << ',';
                    }

                    output << object["message"].dump();

                    if (!not_empty) {
                        not_empty = true;
                    }
                }
            }

            if (filetype == Filetype::JSON) {
                output << ']' << endl;
            }

            input.close();
            output.close();
        }
    }

    void ExtractLogs::init(CLI::App &app) {
        auto extract = app.add_subcommand("aa-extract", "Extract messages from logs");

        extract->add_option("--input1", _input_path, "Input file")->required()->check(CLI::ExistingFile);
        extract->add_option("--param1", _filetype, "Type of input file (CSV/JSON). Default: JSON")
                ->transform(CLI::CheckedTransformer(filetype_map, CLI::ignore_case));
        extract->add_option("--param2", _output_type, "Messages to choose (in/out/all). Default: all")
                ->transform(CLI::CheckedTransformer(output_map, CLI::ignore_case));
        extract->add_option("--output1", _output_path, "Output file")->required();

        extract->callback([&]() { process(_input_path, _filetype, _output_type, _output_path); });
    }
}