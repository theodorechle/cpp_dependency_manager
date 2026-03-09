#ifndef ABSTRACT_INSTALLER_HPP
#define ABSTRACT_INSTALLER_HPP

#include "../../../models/dependency.hpp"
#include <string>

enum class DependencyDownloaderStatus { DONE, ERROR };

class AbstractInstaller {
    virtual DependencyDownloaderStatus download(const std::string &dependencyName, const Version &version, const std::string &outputPath,
                                                std::ostream &stream) const = 0;

    virtual DependencyDownloaderStatus update(const std::string &dependencyName, const Version &version, const std::string &path,
                                              std::ostream &stream) const = 0;

    virtual DependencyDownloaderStatus uninstall(const std::string &dependencyName, const std::string &path, std::ostream &stream) const = 0;
};

#endif // ABSTRACT_INSTALLER_HPP
