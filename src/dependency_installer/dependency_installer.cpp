#include "dependency_installer.hpp"

std::string DependencyInstaller::path(const std::string &dependencyName) const {
    size_t index = dependencyName.find_last_of('/');
    if (index == std::string::npos) return "";
    return dependencyName.substr(index + 1);
}

InstallerStatus DependencyInstaller::download(const Provider &provider, const std::string &dependencyName, const Version &version,
                                              std::ostream &stream) const {
    switch (provider) {
    case Provider::GIT:
        // maybe creating a new Installer instance on each download is a bit overkill (for git, need to run git_libgit2_start and shutdown)
        return GitInstaller().download(dependencyName, version, path(dependencyName), stream);
    default:
        throw std::runtime_error("Downloading from " + providerToString(provider) + " providers is not implemented.");
        break;
    }
}

InstallerStatus DependencyInstaller::update(const Provider &provider, const std::string &dependencyName, const Version &version,
                                            std::ostream &stream) const {
    return InstallerStatus::OTHER_ERROR;
}

InstallerStatus DependencyInstaller::uninstall(const Provider &provider, const std::string &dependencyName, std::ostream &stream) const {
    return InstallerStatus::OTHER_ERROR;
}
