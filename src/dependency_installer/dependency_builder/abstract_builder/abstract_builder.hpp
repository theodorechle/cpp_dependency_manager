#ifndef ABSTRACT_BUILDER_HPP
#define ABSTRACT_BUILDER_HPP

#include <string>

enum class DependencyBuilderStatus { DONE, ERROR };

class AbstractBuilder {
public:
    virtual DependencyBuilderStatus build(const std::string &directory, std::ostream &stream) const = 0;
};

#endif // ABSTRACT_BUILDER_HPP
