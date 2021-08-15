#include <iostream>

#include "incl/CLI11.hpp"

#include "config.h"
#include "subcommands/templater.h"
#include "subcommands/csv2json.h"
#include "subcommands/unique.h"
#include "subcommands/pick.h"

#include "projects/anime-alice/extract.h"

using namespace std;
using namespace AtomicProcessors;

int main(int argc, char **argv) {
    cout << "===========================" << endl;
    cout << "Welcome to AtomicProcessors" << endl;
    cout << "Current version: " << AtomicProcessors_VERSION_MAJOR << "." << AtomicProcessors_VERSION_MINOR << endl;
    cout << "===========================" << endl;

    CLI::App app{"Universal package for processing"};
    app.allow_extras(true);
    app.require_subcommand(1);

    Templater::init(app);
    CSV2JSON::init(app);
    Unique::init(app);
    Pick().init(app);

    AnimeAlice::ExtractLogs().init(app);

    CLI11_PARSE(app, argc, argv);

    return 0;
}
