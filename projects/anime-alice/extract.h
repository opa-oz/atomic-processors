#pragma once

#include <string>
#include <map>
#include <iostream>

#include "../utils/filetype.h"
#include "../incl/CLI11.hpp"

namespace AtomicProcessors::AnimeAlice {
    using namespace std;

    namespace {
        enum class OutputType : int {
            REQUEST,
            RESPONSE,
            MIXED
        };

        string InputMessage{"user_input"};
        string OutputMessage{"answer_to_user"};
    }

    class ExtractLogs {
    public:
        void
        static process(const string &input_path, const Filetype &filetype, const OutputType &output_type,
                       const string &output_path);

        void init(CLI::App &app);

    private:
        string _input_path;
        string _output_path;

        Filetype _filetype{Filetype::JSON};
        OutputType _output_type{OutputType::MIXED};

        map<string, Filetype> filetype_map{{"json", Filetype::JSON},
                                           {"csv",  Filetype::CSV}};
        map<string, OutputType> output_map{{"in",  OutputType::REQUEST},
                                           {"out", OutputType::RESPONSE},
                                           {"all", OutputType::MIXED}};

    };


}