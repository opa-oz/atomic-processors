#include <iostream>
#include <nlohmann/json.hpp>
#include "pick.h"
#include "../utils/string.h"
#include "../utils/read.h"
#include "../utils/json.h"

using json = nlohmann::json;

namespace AtomicProcessors {
    void Pick::init(CLI::App &app) {
        auto pick = app.add_subcommand("pick", "Pick fields from array of objects");

        pick->add_option("--input1", _input_path, "Input file")->required()->check(CLI::ExistingFile);
        pick->add_option("--param1", _fields,
                         "Fields to pick, comma-separated. Example: 'model_id,value,text'")->required();
        pick->add_option("--param2", _flat, "Flat array as output");
        pick->add_option("--output1", _output_path, "Output file")->required();

        pick->callback([&]() { process(_input_path, process_fields(_fields), _flat, _output_path); });
    }

    void
    Pick::process(const string &input_file, const vector<string> &fields, const bool &flat, const string &output_file) {
        auto input = Utils::Read::file2json(input_file);
        ofstream output;
        output.open(output_file);

        cout << "Extracted fields: " << Utils::String::join(fields, ", ") << endl;

        cout << "Lets parse input file" << endl;
        if (!input.is_array()) {
            throw runtime_error("Expected json array");
        }

        output << '[';
        bool not_empty = false;

        cout << "Entities to process: " << std::to_string(input.size()) << endl;
        for (json::iterator it = input.begin(); it != input.end(); ++it) {
            auto value = it.value();
            if (!value.is_object()) {
                throw runtime_error("Expected array of objects!");
            }

            json o = flat ? json::array() : json::object();
            bool picked = false;

            if (flat) {
                const string field = fields[0];
                if (!value[field].empty()) {
                    if (not_empty) {
                        output << ',';
                    }
                    output << value[field];
                    picked = true;

                    if (!not_empty) {
                        not_empty = true;
                    }
                }
            } else {
                for (const auto &field:fields) {
                    if (!value[field].empty()) {
                        Utils::JSON::copy(value[field], o, field);
                        picked = true;
                    }
                }
            }

            if (picked && !flat) {
                if (not_empty) {
                    output << ',';
                }
                output << o.dump();
                if (!not_empty) {
                    not_empty = true;
                }
            }
        }

        output << ']' << endl;
        output.close();
    }

    vector<string> Pick::process_fields(const string &fields) {
        return Utils::String::split(fields, ',');
    }
}

