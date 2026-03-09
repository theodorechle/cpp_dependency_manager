#ifndef GIT_INSTALLER_HPP
#define GIT_INSTALLER_HPP

#include "../abstract_downloader/abstract_downloader.hpp"
#include <git2.h>
#include <iostream>

class GitInstaller : AbstractInstaller {
public:
    GitInstaller();
    ~GitInstaller();

    DependencyDownloaderStatus download(const std::string &dependencyName, const Version &version, const std::string &outputPath,
                                        std::ostream &stream) const override;

    DependencyDownloaderStatus update(const std::string &dependencyName, const Version &version, const std::string &path,
                                      std::ostream &stream) const override;

    DependencyDownloaderStatus uninstall(const std::string &dependencyName, const std::string &path, std::ostream &stream) const override;
};

#endif // GIT_INSTALLER_HPP
