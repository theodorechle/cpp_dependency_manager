#ifndef FIND_REQUIRED_BUILDER_HPP
#define FIND_REQUIRED_BUILDER_HPP

#include "../../models/builder.hpp"
#include <filesystem>
#include <string>

Builder findRequiredBuilder(const std::string &path);

#endif // FIND_REQUIRED_BUILDER_HPP
