#ifndef ARGUMENT_PARSER_HPP
#define ARGUMENT_PARSER_HPP

#include <list>
#include <string>
#include <unordered_map>

class ArgumentException : public std::exception {
    std::string _message;

public:
    ArgumentException(std::string message) : _message(message) {}

    const char *what() const noexcept { return _message.c_str(); }
};

enum class ArgumentType { SHORT, LONG, NO_DASH_FIRST_ARGUMENT };

std::string argumentTypeToString(ArgumentType argumentType);

struct Argument {
    std::list<std::string> values;
    ArgumentType type;
};

typedef std::unordered_map<std::string, Argument> Arguments;

Arguments argumentParser(int argc, char *argv[]);

#endif // ARGUMENT_PARSER_HPP
