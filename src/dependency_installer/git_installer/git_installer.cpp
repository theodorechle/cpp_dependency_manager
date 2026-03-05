#include "git_installer.hpp"

GitInstaller::GitInstaller() { git_libgit2_init(); }

GitInstaller::~GitInstaller() { git_libgit2_shutdown(); }

InstallerStatus GitInstaller::download(const std::string &dependencyName, const Version &version, const std::string &outputPath,
                                       std::ostream &stream) const {
    const git_clone_options options = GIT_CLONE_OPTIONS_INIT;
    git_repository *repository = nullptr;
    int status = git_clone(&repository, dependencyName.data(), outputPath.data(), &options);
    if (status < 0) {
        stream << "Error cloning repository: " << git_error_last()->message << '\n';
        return InstallerStatus::OTHER_ERROR;
    }
    git_repository_free(repository);
    return InstallerStatus::DONE;
}

InstallerStatus GitInstaller::update(const std::string &dependencyName, const Version &version, const std::string &path, std::ostream &stream) const {
    return InstallerStatus::OTHER_ERROR;
}

InstallerStatus GitInstaller::uninstall(const std::string &dependencyName, const std::string &path, std::ostream &stream) const {
    return InstallerStatus::OTHER_ERROR;
}
