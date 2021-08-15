#include <string>
#include <vector>
#include "../incl/CLI11.hpp"

namespace AtomicProcessors {
    using namespace std;

    class Pick {
    public:
        void init(CLI::App &app);

    private:
        static void
        process(const string &input_file, const vector<string> &fields, const bool &flat, const string &output_file);

        static vector<string> process_fields(const string &fields);

        string _input_path;
        string _output_path;
        string _fields;
        bool _flat;
    };
}