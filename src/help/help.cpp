#include "help.hpp"

void showHelp() {
    std::cerr << "dependency manager\n";
    std::cerr << "Arguments:\n";
    std::cerr << "-f | --file <file_name>: dependency file to use\n";
    std::cerr << "-h | --help: show this help\n";
    std::cerr << "-i | --install <provider> <dependency> <version>: install a dependency\n";
}
