#ifndef DEPENDENCY_INSTALLER_HPP
#define DEPENDENCY_INSTALLER_HPP

#include "abstract_installer/abstract_installer.hpp"
#include "git_installer/git_installer.hpp"
#include <ostream>

class DependencyInstaller {
    std::string path(const std::string &dependencyName) const;

public:
    InstallerStatus download(const Provider &provider, const std::string &dependencyName, const Version &version, std::ostream &stream) const;

    InstallerStatus update(const Provider &provider, const std::string &dependencyName, const Version &version, std::ostream &stream) const;

    InstallerStatus uninstall(const Provider &provider, const std::string &dependencyName, std::ostream &stream) const;
};

#endif // DEPENDENCY_INSTALLER_HPP
