#include "iostream"
#include "text_clean.h"
#include "../utils/read.h"
#include "../utils/string.h"

#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace AtomicProcessors {

    void TextCleanUp::init(CLI::App &app) {
        auto text_clean_up = app.add_subcommand("txt-cleanup", "Clean text from JSON array");

        text_clean_up->add_option("--input1", _input_path, "Input file")->required()->check(CLI::ExistingFile);
        text_clean_up->add_option("--output2", _map_path, "Map file")->required();
        text_clean_up->add_option("--output1", _output_path, "Output file")->required();

        text_clean_up->callback([&]() { process(_input_path, _map_path, _output_path); });
    }

    void TextCleanUp::process(const string &input_file, const string &map_file, const string &output_file) {
        json input = Utils::Read::file2json(input_file);
        ofstream output;
        ofstream mp;

        output.open(output_file);
        mp.open(map_file);

        cout << "Lets parse input file" << endl;
        if (!input.is_array()) {
            throw runtime_error("Expected json array");
        }
        cout << "Entities to process: " << std::to_string(input.size()) << endl;
        bool not_empty = false;

        output << '[';
        mp << '[';

        for (json::iterator it = input.begin(); it != input.end(); ++it) {
            auto v = it.value();
            if (!v.is_string()) {
                throw runtime_error("Expected array of strings!");
            }
            const string value = process_one_line(v.get<string>());

            if (!value.empty()) {
                if (not_empty) {
                    output << ',';
                    mp << ',';
                }

                output << json(value).dump();
                mp << json({v.get<string>(), value}).dump();

                if (!not_empty) {
                    not_empty = true;
                }
            }
        }

        output << ']' << endl;
        mp << ']' << endl;

        output.close();
        mp.close();
    }

    string TextCleanUp::process_one_line(const string &s) {
        return Utils::String::to_lower_copy(Utils::String::trim(s));
    }
}