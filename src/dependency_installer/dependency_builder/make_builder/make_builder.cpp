#include "make_builder.hpp"

DependencyBuilderStatus MakeBuilder::build(const std::string &directory, std::ostream &stream) const {
    std::string command = "cd " + directory + " && make";
    return system(command.c_str()) ? DependencyBuilderStatus::ERROR : DependencyBuilderStatus::DONE;
}
