#include "help.hpp"

void showHelp() {
    std::cerr << "dependency manager\n";
    std::cerr << "Arguments:\n";
    std::cerr << "--file <file_name>: dependency file to use\n";
    std::cerr << "-h | --help: show this help\n";
}
