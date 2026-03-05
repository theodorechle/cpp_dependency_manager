#ifndef GIT_INSTALLER_HPP
#define GIT_INSTALLER_HPP

#include "../abstract_installer/abstract_installer.hpp"
#include <git2.h>
#include <iostream>

class GitInstaller : AbstractInstaller {
public:
    GitInstaller();
    ~GitInstaller();

    InstallerStatus download(const std::string &dependencyName, const Version &version, const std::string &outputPath,
                             std::ostream &stream) const override;

    InstallerStatus update(const std::string &dependencyName, const Version &version, const std::string &path, std::ostream &stream) const override;

    InstallerStatus uninstall(const std::string &dependencyName, const std::string &path, std::ostream &stream) const override;
};

#endif // GIT_INSTALLER_HPP
