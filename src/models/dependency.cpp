#include "dependency.hpp"

std::string providerToString(Provider provider) {
    switch (provider) {
    case Provider::GIT:
        return "git";
    default:
        throw std::runtime_error("Invalid provider");
    }
}

std::string versionTypeToString(VersionType type) {
    switch (type) {
    case VersionType::EXACT:
        return "exact";
    case VersionType::LAST:
        return "last";
    default:
        throw std::runtime_error("Invalid version type");
    }
}

std::string versionToString(Version version) {
    switch (version.type) {
    case VersionType::EXACT:
        return version.id;
    case VersionType::LAST:
        return "(last)";
    default:
        throw std::runtime_error("Invalid version type");
    }
}
