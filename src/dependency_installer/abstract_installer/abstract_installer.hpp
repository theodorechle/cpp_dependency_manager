#ifndef ABSTRACT_INSTALLER_HPP
#define ABSTRACT_INSTALLER_HPP

#include "../../models/dependency.hpp"
#include <string>

enum class InstallerStatus { DONE, NO_NETWORK, FILE_ACCESS, OTHER_ERROR };

class AbstractInstaller {
    virtual InstallerStatus download(const std::string &dependencyName, const Version &version, const std::string &outputPath,
                                     std::ostream &stream) const = 0;

    virtual InstallerStatus update(const std::string &dependencyName, const Version &version, const std::string &path,
                                   std::ostream &stream) const = 0;

    virtual InstallerStatus uninstall(const std::string &dependencyName, const std::string &path, std::ostream &stream) const = 0;
};

#endif // ABSTRACT_INSTALLER_HPP
