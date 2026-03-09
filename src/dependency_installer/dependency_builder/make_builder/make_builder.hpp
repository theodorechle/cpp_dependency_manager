#ifndef MAKE_BUILDER_HPP
#define MAKE_BUILDER_HPP

#include "../abstract_builder/abstract_builder.hpp"

class MakeBuilder : AbstractBuilder {
public:
    DependencyBuilderStatus build(const std::string &directory, std::ostream &stream) const override;
};

#endif // MAKE_BUILDER_HPP
