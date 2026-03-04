#ifndef ARGUMENT_PARSER_HPP
#define ARGUMENT_PARSER_HPP

#include "../models/argument.hpp"

class ArgumentException : public std::exception {
    std::string _message;

public:
    ArgumentException(std::string message) : _message(message) {}

    const char *what() const noexcept { return _message.c_str(); }
};

Arguments argumentParser(int argc, const char *const argv[]);

#endif // ARGUMENT_PARSER_HPP
