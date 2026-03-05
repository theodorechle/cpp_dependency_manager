#include "commands_executor.hpp"

namespace {
    bool findArgument(const Arguments &arguments, std::list<std::pair<std::string, ArgumentType>> allowedArguments, ArgumentValues *values,
                      int minValues = 0, int maxValues = std::numeric_limits<int>::max()) {
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

void commandsExecutor(Arguments arguments, std::ostream &stream) {
    ArgumentValues values = {};
    bool commandsExecuted = false;

    if (findArgument(arguments, {{"file", ArgumentType::LONG}, {"f", ArgumentType::SHORT}}, &values, 1, 1)) {
        std::list<Dependency *> dependencies = readDependenciesFromFile(values.front());
        for (Dependency *dependency : dependencies) {
            std::cerr << "installing dependency " << dependency->name << " with version " << versionToString(dependency->version) << " ...\n";
            InstallerStatus status = DependencyInstaller().download(dependency->provider, dependency->name, dependency->version, stream);
            switch (status) {
            case InstallerStatus::DONE:
                std::cerr << "done\n";
                break;
            case InstallerStatus::NO_NETWORK:
                std::cerr << "no network, aborting installation\n";
                return;
            default:
                break;
            }
        }

        commandsExecuted = true;
    }

    if (findArgument(arguments, {{"help", ArgumentType::LONG}, {"h", ArgumentType::SHORT}}, &values, 0, 0)) {
        showHelp();
        commandsExecuted = true;
    }

    if (!commandsExecuted) {
        std::cerr << "no command executed\n\n";
        showHelp();
    }
}
