#ifndef DEPENDENCY_HPP
#define DEPENDENCY_HPP

#include <string>
#include <stdexcept>

enum class Provider { GIT, INVALID };

std::string providerToString(Provider provider);

enum class VersionType {
    EXACT,
    LAST,
};

std::string versionTypeToString(VersionType type);

struct Version {
    VersionType type;
    std::string id;
};

struct Dependency {
    Provider provider;
    std::string name;
    Version version;
};

#endif // DEPENDENCY_HPP