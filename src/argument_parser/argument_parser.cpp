#include "argument_parser.hpp"

std::string argumentTypeToString(ArgumentType argumentType) {
    switch (argumentType) {
    case ArgumentType::SHORT:
        return "short";
    case ArgumentType::LONG:
        return "long";
    case ArgumentType::NO_DASH_FIRST_ARGUMENT:
        return "no dash first argument";
    default:
        throw ArgumentException("invalid argument type");
    }
}

Arguments argumentParser(int argc, const char *const argv[]) {
    Arguments arguments = Arguments();

    int index = 1; // skip first argument, which is just the path to the current program
    std::string lastArgument = "";
    while (index < argc) {
        const char *argument = argv[index];
        if (argument[0] == '-') {
            if (argument[1] == '-') { // long argument
                std::string argumentWithoutDashes = std::string(argument).substr(2);
                arguments.insert({argumentWithoutDashes, Argument{ArgumentType::LONG}});
                lastArgument = argumentWithoutDashes;
            }
            else { // one or more short arguments
                const char *shortArgument = argument + 1;

                while (*shortArgument != '\0') {
                    std::string argumentWithoutDash = std::string(1, *shortArgument);
                    arguments.insert({argumentWithoutDash, Argument{ArgumentType::SHORT}});
                    shortArgument++;
                    lastArgument = argumentWithoutDash;
                }
            }
        }
        else {
            if (arguments.size()) {
                // add value to previous argument
                Arguments::iterator argIterator = arguments.find(lastArgument);
                if (argIterator != arguments.end()) argIterator->second.values.push_back(argument);
            }
            else {
                // first argument, without dashes
                arguments.insert({argument, Argument{ArgumentType::NO_DASH_FIRST_ARGUMENT}});
                lastArgument = argument;
            }
        }
        index++;
    }
    return arguments;
}
