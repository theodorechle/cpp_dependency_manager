#include "dependency_solver.hpp"

namespace {
    constexpr std::array<char, 5> allowedCharsInDependencyName = {'_', ':', '/', '-', '.'};

    size_t parseProviderName(const std::string &text, size_t start) {
        if (start >= text.size()) return 0;
        for (size_t i = start; i < text.size(); i++) {
            if (!std::isalnum(text[i]) && text[i] != '-' && text[i] != '_') return i - start;
        }
        return text.size() - start;
    }

    size_t parseDependencyName(const std::string &text, size_t start) {
        if (start >= text.size()) return 0;
        for (size_t i = start; i < text.size(); i++) {
            if (!std::isalnum(text[i])) {
                bool found = false;
                for (char c : allowedCharsInDependencyName) {
                    if (text[i] == c) {
                        found = true;
                        break;
                    }
                }
                if (!found) return i - start;
            }
        }
        return text.size() - start;
    }

    size_t parseVersion(const std::string &text, size_t start) {
        if (start >= text.size()) return 0;
        size_t i = start;
        if (text[start] == '#') {
            i++;
        }
        for (; i < text.size(); i++) {
            if (!std::isalnum(text[i]) && text[i] != '-' && text[i] != '_') return i - start;
        }
        return text.size() - start;
    }

    size_t parseSpacesAndTabs(const std::string &text, size_t start) {
        size_t i = start;
        while (i < text.size()) {
            char c = text[i];
            if (c != ' ' && c != '\t') return i - start;
            i++;
        }
        return text.size() - start;
    }

    void toLowerCase(std::string &value) {
        for (char &c : value) {
            if (c >= 'A' && c <= 'Z') {
                c += 32;
            }
        }
    }
} // namespace

Provider providerNameToEnum(std::string providerName) {
    toLowerCase(providerName);
    if (providerName == "git") return Provider::GIT;
    else return Provider::UNKNOWN;
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

Dependency *readDependency(std::string line) {
    /* dependency line should be like this:
    provider dependency-name version
    If version is not provided, it count as the last available version.
    For git providen dependencies, version should be the commit ref.
    Example:
    git my-project #aa5f478
     */

    size_t charIndex = 0;

    // possible characters at beginning of line
    charIndex += parseSpacesAndTabs(line, charIndex);
    if (charIndex == line.size()) {
        std::cerr << "Empty dependency line\n";
        return nullptr;
    }

    size_t providerNameLength = parseProviderName(line, charIndex);
    if (providerNameLength == 0) {
        std::cerr << "Invalid provider name, can't start with '" << line[charIndex] << "'\n";
        return nullptr;
    }

    // provider
    Provider provider = providerNameToEnum(line.substr(charIndex, providerNameLength));
    if (provider == Provider::UNKNOWN) {
        std::cerr << "Invalid provider '" << line.substr(charIndex, providerNameLength) << "'\n";
        return nullptr;
    }
    charIndex += providerNameLength;

    size_t spacesLength = parseSpacesAndTabs(line, charIndex);
    if (spacesLength == 0) {
        std::cerr << "Provider and dependency must be space or tab separated\n";
        return nullptr;
    }
    charIndex += spacesLength;

    // dependency
    size_t dependencyNameLength = parseDependencyName(line, charIndex);
    if (dependencyNameLength == 0) {
        std::cerr << "No dependency given\n";
        return nullptr;
    }
    std::string dependencyName = line.substr(charIndex, dependencyNameLength);
    charIndex += dependencyNameLength;

    spacesLength = parseSpacesAndTabs(line, charIndex);
    if (spacesLength == 0 && charIndex + spacesLength < line.size()) {
        std::cerr << "Dependency and version must be space or tab separated\n";
        return nullptr;
    }
    charIndex += spacesLength;

    // version
    size_t versionLength = parseVersion(line, charIndex);
    Version version = versionStringToVersion(line, charIndex, versionLength);
    charIndex += versionLength;

    // possible characters at end of line
    spacesLength = parseSpacesAndTabs(line, charIndex);
    if (charIndex + spacesLength < line.size()) {
        std::cerr << "Unexpected argument after ";
        if (version.type == VersionType::LAST) std::cerr << "dependency";
        else std::cerr << "version";
        std::cerr << "\n";
        return nullptr;
    }

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
    else {
        std::cerr << "Couldn't open file '" << fileName << "'\n";
    }

    return dependencies;
}