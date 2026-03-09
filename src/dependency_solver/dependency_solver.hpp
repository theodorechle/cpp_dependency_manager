#ifndef DEPENDENCY_SOLVER_HPP
#define DEPENDENCY_SOLVER_HPP

#include "../models/dependency.hpp"
#include <array>
#include <fstream>
#include <iostream>
#include <list>
#include <string>

Provider providerNameToEnum(std::string providerName);

Version versionStringToVersion(std::string line, size_t start, size_t length);

// return parsed dependency or nullptr if couldn't have been parsed
Dependency *readDependency(std::string line);
std::list<Dependency *> readDependenciesFromFile(const std::string &fileName);

#endif // DEPENDENCY_SOLVER_HPP
