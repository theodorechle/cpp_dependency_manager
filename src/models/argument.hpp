#ifndef ARGUMENT_HPP
#define ARGUMENT_HPP

#include <list>
#include <string>
#include <unordered_map>

enum class ArgumentType { SHORT, LONG, NO_DASH_FIRST_ARGUMENT };

std::string argumentTypeToString(ArgumentType argumentType);

typedef std::list<std::string> ArgumentValues;

struct Argument {
    ArgumentType type;
    ArgumentValues values = {};
};

typedef std::unordered_map<std::string, Argument> Arguments;

#endif // ARGUMENT_HPP
