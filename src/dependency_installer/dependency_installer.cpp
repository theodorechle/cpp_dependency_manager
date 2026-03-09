#include "dependency_installer.hpp"

std::string DependencyInstaller::path(const std::string &dependencyName) const {
    size_t index = dependencyName.find_last_of('/');
    if (index == std::string::npos) return "";
    return dependencyName.substr(index + 1);
}

DependencyDownloaderStatus DependencyInstaller::download(const Provider &provider, const std::string &dependencyName, const Version &version,
                                                         std::ostream &stream) const {
    stream << "Downloading " << dependencyName << ":" << versionToString(version) << "\n";
    switch (provider) {
    case Provider::GIT:
        // maybe creating a new Installer instance on each download is a bit overkill (for git, need to run git_libgit2_start and shutdown)
        return GitInstaller().download(dependencyName, version, path(dependencyName), stream);
    default:
        throw std::runtime_error("Downloading from " + providerToString(provider) + " providers is not implemented.");
    }
}

DependencyBuilderStatus DependencyInstaller::build(const Provider &provider, const std::string &dependencyName, const Version &version,
                                                   std::ostream &stream) const {
    stream << "Building " << dependencyName << ":" << versionToString(version) << "\n";
    switch (findRequiredBuilder(path(dependencyName))) {
    case Builder::MAKE:
        // maybe creating a new Builder instance on each download is a bit overkill
        return MakeBuilder().build(path(dependencyName), stream);
    default:
        throw std::runtime_error("No known building file");
    }
}

DependencyInstallerStatus DependencyInstaller::install(const Provider &provider, const std::string &dependencyName, const Version &version,
                                                       std::ostream &stream) const {
    if (download(provider, dependencyName, version, stream) != DependencyDownloaderStatus::DONE) return DependencyInstallerStatus::ERROR;
    if (build(provider, dependencyName, version, stream) != DependencyBuilderStatus::DONE) return DependencyInstallerStatus::ERROR;
    return DependencyInstallerStatus::DONE;
}

DependencyInstallerStatus DependencyInstaller::update(const Provider &provider, const std::string &dependencyName, const Version &version,
                                                      std::ostream &stream) const {
    return DependencyInstallerStatus::ERROR;
}

DependencyInstallerStatus DependencyInstaller::uninstall(const Provider &provider, const std::string &dependencyName, std::ostream &stream) const {
    return DependencyInstallerStatus::ERROR;
}
