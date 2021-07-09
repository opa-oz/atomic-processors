#include <iostream>

#include "CLI/App.hpp"
#include "CLI/Formatter.hpp"
#include "CLI/Config.hpp"

#include "subcommands/templater.cpp"
#include "subcommands/csv2json.cpp"
#include "subcommands/unique.cpp"

using namespace std;

int main(int argc, char **argv)
{
    CLI::App app{"Universal package for processing"};
    app.allow_extras(true);
    app.require_subcommand(1);

    Templater::init(app);
    CSV2JSON::init(app);
    Unique::init(app);

    CLI11_PARSE(app, argc, argv);

    return 0;
}