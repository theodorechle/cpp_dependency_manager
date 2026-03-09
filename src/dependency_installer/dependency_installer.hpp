#ifndef DEPENDENCY_INSTALLER_HPP
#define DEPENDENCY_INSTALLER_HPP

#include "dependency_builder/abstract_builder/abstract_builder.hpp"
#include "dependency_builder/find_required_builder.hpp"
#include "dependency_builder/make_builder/make_builder.hpp"
#include "dependency_downloader/abstract_downloader/abstract_downloader.hpp"
#include "dependency_downloader/git_downloader/git_downloader.hpp"
#include <ostream>

enum class DependencyInstallerStatus { DONE, ERROR };

class DependencyInstaller {
    std::string path(const std::string &dependencyName) const;

public:
    DependencyDownloaderStatus download(const Provider &provider, const std::string &dependencyName, const Version &version,
                                        std::ostream &stream) const;

    DependencyBuilderStatus build(const Provider &provider, const std::string &dependencyName, const Version &version, std::ostream &stream) const;

    DependencyInstallerStatus install(const Provider &provider, const std::string &dependencyName, const Version &version,
                                      std::ostream &stream) const;

    DependencyInstallerStatus update(const Provider &provider, const std::string &dependencyName, const Version &version, std::ostream &stream) const;

    DependencyInstallerStatus uninstall(const Provider &provider, const std::string &dependencyName, std::ostream &stream) const;
};

#endif // DEPENDENCY_INSTALLER_HPP
