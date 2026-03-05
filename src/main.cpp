#include "argument_parser/argument_parser.hpp"
#include "commands_executor/commands_executor.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
    std::ostream &stream = std::cerr;
    Arguments arguments = argumentParser(argc, argv);
    commandsExecutor(arguments, stream);
    return EXIT_SUCCESS;
}
