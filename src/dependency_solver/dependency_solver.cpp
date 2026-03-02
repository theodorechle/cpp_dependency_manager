#include "dependency_solver.hpp"

namespace {
    size_t parseName(const std::string &line, size_t start) {
        if (start >= line.size()) return 0;
        for (size_t i = start; i < line.size(); i++) {
            if (!std::isalnum(line[i]) && line[i] != '-' && line[i] != '_') return i - start;
        }
        return line.size() - start;
    }

    size_t parseVersion(const std::string &line, size_t start) {
        if (start >= line.size()) return 0;
        size_t i = start;
        if (line[start] == '#') {
            i++;
        }
        for (; i < line.size(); i++) {
            if (!std::isalnum(line[i]) && line[i] != '-' && line[i] != '_') return i - start;
        }
        return line.size() - start;
    }

    void toLowerCase(std::string &value) {
        for (char &c : value) {
            if (c >= 'A' && c <= 'Z') {
                c += 32;
            }
        }
    }

    Provider providerNameToEnum(std::string providerName) {
        toLowerCase(providerName);
        if (providerName == "git") return Provider::GIT;
        else return Provider::INVALID;
    }

    Version versionStringToVersion(std::string line, size_t start, size_t length) {
        Version version = Version();
        if (length == 0) {
            version.type = VersionType::LAST;
            version.id = "";
        }
        else {
            version.id = line.substr(start, length);
            version.type = VersionType::EXACT;
        }
        return version;
    }
} // namespace

Dependency *readDependency(std::string line) {
    /* dependency line should be like this:
    provider dependency-name version
    If version is not provided, it count as the last available version.
    For git providen dependencies, version should be the commit ref.
    Example:
    git my-project #aa5f478
     */

    size_t providerNameLength = parseName(line, 0);
    if (providerNameLength == 0) {
        std::cerr << "Empty dependency line\n";
        return nullptr;
    }
    Provider provider = providerNameToEnum(line.substr(0, providerNameLength));
    if (provider == Provider::INVALID) {
        std::cerr << "Invalid provider '" << line.substr(0, providerNameLength) << "'\n";
        return nullptr;
    }

    size_t dependencyNameLength = parseName(line, providerNameLength + 1);
    if (dependencyNameLength == 0) {
        std::cerr << "No dependency given\n";
        return nullptr;
    }
    std::string dependencyName = line.substr(providerNameLength + 1, dependencyNameLength);

    size_t versionLength = parseVersion(line, providerNameLength + dependencyNameLength + 2);
    Version version = versionStringToVersion(line, providerNameLength + dependencyNameLength + 2, versionLength);

    return new Dependency{provider, dependencyName, version};
}

std::list<Dependency *> readDependenciesFromFile(const std::string &fileName) {
    std::list<Dependency *> dependencies = {};

    std::string line;
    std::ifstream file(fileName);
    if (file.is_open()) {
        while (getline(file, line)) {
            Dependency *dependency = readDependency(line);
            if (dependency != nullptr) dependencies.push_back(dependency);
        }
    }
    return dependencies;
}