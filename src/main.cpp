#include "argument_parser/argument_parser.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
    Arguments arguments = argumentParser(argc, argv);
    for (std::pair<std::string, Argument> arg : arguments) {
        std::cerr << arg.first << " (" << argumentTypeToString(arg.second.type) << ")";
        if (arg.second.values.size()) std::cerr << ":";
        for (std::string value : arg.second.values) {
            std::cerr << " " << value;
        }
        std::cerr << "\n";
    }
    return EXIT_SUCCESS;
}
