#pragma once

#include <map>
#include <string>
#include <nlohmann/json.hpp>
#include "../utils/filetype.h"
#include "../incl/CLI11.hpp"

namespace AtomicProcessors::Unique {
    using namespace std;
    using json = nlohmann::json;

    enum class Datatype : int {
        Simple,
        Complex
    };

    namespace {
        string _input_path;
        string _output_path;
        string _keys;

        Filetype _filetype{Filetype::JSON};
        Datatype _datatype{Datatype::Simple};

        map<string, Filetype> filetype_map{{"json", Filetype::JSON},
                                           {"csv",  Filetype::CSV}};
        map<string, Datatype> datatype_map{{"simple",  Datatype::Simple},
                                           {"complex", Datatype::Complex}};
    }

    void process(const string &input_path, const Filetype &filetype, const Datatype &datatype, const string &_keys,
                 const string &output_path);

    void init(CLI::App &app);
}