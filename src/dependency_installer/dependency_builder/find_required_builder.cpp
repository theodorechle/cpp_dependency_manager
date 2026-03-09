#include "find_required_builder.hpp"
#include <iostream>

Builder findRequiredBuilder(const std::string &path) {
    if (std::filesystem::exists(std::filesystem::path(path).append("Makefile"))) {
        return Builder::MAKE;
    }
    return Builder::UNKNOWN;
}