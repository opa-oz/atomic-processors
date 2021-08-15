#include <string>
#include "../incl/CLI11.hpp"

namespace AtomicProcessors {
    using namespace std;

    class TextCleanUp {
    public:
        void init(CLI::App &app);

    private:
        static void process(const string &input_file, const string &map_file, const string &output_file);

        static string process_one_line(const string &s);

        string _input_path;
        string _map_path;
        string _output_path;
    };
}