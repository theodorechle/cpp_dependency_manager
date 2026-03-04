#include "commands_executor.hpp"

namespace {
    bool findArgument(const Arguments &arguments, std::list<std::pair<std::string, ArgumentType>> allowedArguments, int minValues, int maxValues,
                      ArgumentValues *values) {
        for (std::pair<std::string, ArgumentType> allowedArgument : allowedArguments) {
            Arguments::const_iterator argumentsIterator = arguments.find(allowedArgument.first);
            if (argumentsIterator != arguments.cend() && argumentsIterator->second.type == allowedArgument.second) {
                int nbValues = argumentsIterator->second.values.size();
                if (nbValues < minValues) {
                    std::cerr
                        << "for argument '"
                        << allowedArgument.first
                        << "' ("
                        << argumentTypeToString(allowedArgument.second)
                        << "), expected at list "
                        << minValues
                        << " values, got "
                        << nbValues
                        << "\n";
                    return false;
                }
                if (nbValues > maxValues) {
                    std::cerr
                        << "for argument '"
                        << allowedArgument.first
                        << "' ("
                        << argumentTypeToString(allowedArgument.second)
                        << "), expected at most "
                        << maxValues
                        << " values, got "
                        << nbValues
                        << "\n";
                    return false;
                }
                *values = argumentsIterator->second.values;
                return true;
            }
        }
        return false;
    }
} // namespace

void commandsExecutor(Arguments arguments) {
    ArgumentValues values = {};
    bool commandsExecuted = false;

    if (findArgument(arguments, {{"file", ArgumentType::LONG}, {"f", ArgumentType::SHORT}}, 1, 1, &values)) {
        readDependenciesFromFile(values.front());
        commandsExecuted = true;
    }

    if (findArgument(arguments, {{"help", ArgumentType::LONG}, {"h", ArgumentType::SHORT}}, 0, 0, &values)) {
        showHelp();
        commandsExecuted = true;
    }

    if (!commandsExecuted) {
        std::cerr << "no command executed\n\n";
        showHelp();
    }
}
