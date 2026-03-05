#ifndef COMMANDS_EXECUTOR_HPP
#define COMMANDS_EXECUTOR_HPP

#include "../dependency_installer/dependency_installer.hpp"
#include "../dependency_solver/dependency_solver.hpp"
#include "../help/help.hpp"
#include "../models/argument.hpp"
#include <limits>
#include <ostream>

void commandsExecutor(Arguments arguments, std::ostream &stream);

#endif // COMMANDS_EXECUTOR_HPP
