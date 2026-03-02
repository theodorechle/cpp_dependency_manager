#include "argument_parser/argument_parser.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
    Arguments arguments = argumentParser(argc, argv);
    return EXIT_SUCCESS;
}
