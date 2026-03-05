#include "dependency_solver_tests.hpp"

namespace dependencySolverTests {
    void displayDependency(const Dependency *dependency) {
        if (dependency == nullptr) std::cerr << "no dependency\n";
        std::cerr
            << "dependency: provider="
            << providerToString(dependency->provider)
            << ", name="
            << dependency->name
            << ", version="
            << dependency->version.id
            << "("
            << versionTypeToString(dependency->version.type)
            << ")\n";
    }

    bool compareDependencies(const Dependency *expected, const Dependency *actual) {
        if (expected == nullptr && actual != nullptr) {
            std::cerr << "expected nullptr, but actual is not\n";
            return false;
        }
        else if (expected != nullptr && actual == nullptr) {
            std::cerr << "expected a value, but actual is nullptr\n";
            return false;
        }
        else if (expected->name != actual->name) {
            std::cerr << "expected name '" << expected->name << "', got '" << actual->name << "'";
            return false;
        }
        else if (expected->provider != actual->provider) {
            std::cerr << "expected provider '" << providerToString(expected->provider) << "', got '" << providerToString(actual->provider) << "'";
            return false;
        }
        else if (expected->version.id != actual->version.id) {
            std::cerr << "expected version id '" << expected->version.id << "', got '" << actual->version.id << "'\n";
            return false;
        }
        else if (expected->version.type != actual->version.type) {
            std::cerr
                << "expected version type '"
                << versionTypeToString(expected->version.type)
                << "', got '"
                << versionTypeToString(actual->version.type)
                << "'\n";
            return false;
        }
        return true;
    }

    test::Result testReadDependencyWithEmptyLine() {
        Dependency *dependency = readDependency("");
        if (dependency != nullptr) {
            std::cerr << "dependency is not null but should be:\n";
            displayDependency(dependency);
            return test::Result::FAILURE;
        }
        return test::Result::SUCCESS;
    }

    test::Result testReadDependencyWithOnlyProvider() {
        Dependency *dependency = readDependency("git");
        if (dependency != nullptr) {
            std::cerr << "dependency is not null but should be:\n";
            displayDependency(dependency);
            return test::Result::FAILURE;
        }
        return test::Result::SUCCESS;
    }

    test::Result testReadDependencyWithValidProvider() {
        Dependency *dependency = readDependency("git dependency");
        Dependency expected = Dependency{Provider::GIT, "dependency", Version{VersionType::LAST, ""}};
        return test::booleanToResult(compareDependencies(&expected, dependency));
    }

    test::Result testReadDependencyWithInvalidProvider() {
        Dependency *dependency = readDependency("gazergit dependency");
        if (dependency != nullptr) {
            std::cerr << "dependency is not null but should be:\n";
            displayDependency(dependency);
            return test::Result::FAILURE;
        }
        return test::Result::SUCCESS;
    }

    test::Result testReadDependencyWithVersion() {
        Dependency *dependency = readDependency("git dependency #aaax54b");
        Dependency expected = Dependency{Provider::GIT, "dependency", Version{VersionType::EXACT, "#aaax54b"}};
        return test::booleanToResult(compareDependencies(&expected, dependency));
    }

    test::Result testReadDependencyWithoutCommitRefSharpInVersion() {
        Dependency *dependency = readDependency("git dependency aaax54b");
        Dependency expected = Dependency{Provider::GIT, "dependency", Version{VersionType::EXACT, "aaax54b"}};
        return test::booleanToResult(compareDependencies(&expected, dependency));
    }

    test::Result testReadDependencyWithNewlineBetweenProviderAndDependency() {
        Dependency *dependency = readDependency("git\ndependency #aaax54b");
        if (dependency != nullptr) {
            std::cerr << "dependency is not null but should be:\n";
            displayDependency(dependency);
            return test::Result::FAILURE;
        }
        return test::Result::SUCCESS;
    }

    test::Result testReadDependencyWithNewlineBetweenDependencyAndVersion() {
        Dependency *dependency = readDependency("git dependency\n#aaax54b");
        if (dependency != nullptr) {
            std::cerr << "dependency is not null but should be:\n";
            displayDependency(dependency);
            return test::Result::FAILURE;
        }
        return test::Result::SUCCESS;
    }

    test::Result testReadDependencyWithMultipleSpacesBetweenProviderAndDependency() {
        Dependency *dependency = readDependency("git   dependency #aaax54b");
        Dependency expected = Dependency{Provider::GIT, "dependency", Version{VersionType::EXACT, "#aaax54b"}};
        return test::booleanToResult(compareDependencies(&expected, dependency));
    }

    test::Result testReadDependencyWithMultipleSpacesBetweenDependencyAndVersion() {
        Dependency *dependency = readDependency("git dependency  #aaax54b");
        Dependency expected = Dependency{Provider::GIT, "dependency", Version{VersionType::EXACT, "#aaax54b"}};
        return test::booleanToResult(compareDependencies(&expected, dependency));
    }

    test::Result testReadDependencyWithTabBetweenProviderAndDependency() {
        Dependency *dependency = readDependency("git\tdependency #aaax54b");
        Dependency expected = Dependency{Provider::GIT, "dependency", Version{VersionType::EXACT, "#aaax54b"}};
        return test::booleanToResult(compareDependencies(&expected, dependency));
    }

    test::Result testReadDependencyWithTabBetweenDependencyAndVersion() {
        Dependency *dependency = readDependency("git dependency\t#aaax54b");
        Dependency expected = Dependency{Provider::GIT, "dependency", Version{VersionType::EXACT, "#aaax54b"}};
        return test::booleanToResult(compareDependencies(&expected, dependency));
    }

    test::Result testReadDependencyWithMultipleTabsBetweenProviderAndDependency() {
        Dependency *dependency = readDependency("git\t\tdependency #aaax54b");
        Dependency expected = Dependency{Provider::GIT, "dependency", Version{VersionType::EXACT, "#aaax54b"}};
        return test::booleanToResult(compareDependencies(&expected, dependency));
    }

    test::Result testReadDependencyWithMultipleTabsBetweenDependencyAndVersion() {
        Dependency *dependency = readDependency("git dependency\t\t#aaax54b");
        Dependency expected = Dependency{Provider::GIT, "dependency", Version{VersionType::EXACT, "#aaax54b"}};
        return test::booleanToResult(compareDependencies(&expected, dependency));
    }

    test::Result testReadDependencyWithSpacesAndTabsBetweenProviderAndDependency() {
        Dependency *dependency = readDependency("git\t dependency #aaax54b");
        Dependency expected = Dependency{Provider::GIT, "dependency", Version{VersionType::EXACT, "#aaax54b"}};
        return test::booleanToResult(compareDependencies(&expected, dependency));
    }

    test::Result testReadDependencyWithSpacesAndTabsBetweenDependencyAndVersion() {
        Dependency *dependency = readDependency("git dependency \t #aaax54b");
        Dependency expected = Dependency{Provider::GIT, "dependency", Version{VersionType::EXACT, "#aaax54b"}};
        return test::booleanToResult(compareDependencies(&expected, dependency));
    }

    test::Result testReadDependencyWithoutSpaceBetweenDependencyAndVersion() {
        Dependency *dependency = readDependency("git dependency#aaax54b");
        if (dependency != nullptr) {
            std::cerr << "dependency is not null but should be:\n";
            displayDependency(dependency);
            return test::Result::FAILURE;
        }
        return test::Result::SUCCESS;
    }

    test::Result testReadDependencyWithSpacesAfterVersion() {
        Dependency *dependency = readDependency("git dependency #aaax54b      ");
        Dependency expected = Dependency{Provider::GIT, "dependency", Version{VersionType::EXACT, "#aaax54b"}};
        return test::booleanToResult(compareDependencies(&expected, dependency));
    }

    test::Result testReadDependencyWithSpacesAfterDependencyWithoutVersion() {
        Dependency *dependency = readDependency("git dependency      ");
        Dependency expected = Dependency{Provider::GIT, "dependency", Version{VersionType::LAST, ""}};
        return test::booleanToResult(compareDependencies(&expected, dependency));
    }

    test::Result testReadDependencyWithSpacesBeforeProvider() {
        Dependency *dependency = readDependency("   git dependency #aaax54b");
        Dependency expected = Dependency{Provider::GIT, "dependency", Version{VersionType::EXACT, "#aaax54b"}};
        return test::booleanToResult(compareDependencies(&expected, dependency));
    }

    test::Result testReadDependencyWithCharsAfterVersion() {
        Dependency *dependency = readDependency("git dependency #aaax54b dsfghj");
        if (dependency != nullptr) {
            std::cerr << "dependency is not null but should be:\n";
            displayDependency(dependency);
            return test::Result::FAILURE;
        }
        return test::Result::SUCCESS;
    }

    test::Result testReadDependencyWithSpecialCharacterInProvider() {
        Dependency *dependency = readDependency("g$it dependency #aaax54b");
        if (dependency != nullptr) {
            std::cerr << "dependency is not null but should be:\n";
            displayDependency(dependency);
            return test::Result::FAILURE;
        }
        return test::Result::SUCCESS;
    }

    test::Result testReadDependencyWithSpecialCharacterInDependency() {
        Dependency *dependency = readDependency("git depend=ency #aaax54b");
        if (dependency != nullptr) {
            std::cerr << "dependency is not null but should be:\n";
            displayDependency(dependency);
            return test::Result::FAILURE;
        }
        return test::Result::SUCCESS;
    }

    test::Result testReadDependencyWithSpecialCharacterInVersion() {
        Dependency *dependency = readDependency("git dependency #aaax~54b");
        if (dependency != nullptr) {
            std::cerr << "dependency is not null but should be:\n";
            displayDependency(dependency);
            return test::Result::FAILURE;
        }
        return test::Result::SUCCESS;
    }

    test::Result testReadDependencyWithInvalidFirstProviderCharacter() {
        Dependency *dependency = readDependency("#git dependency #aaax54b");
        if (dependency != nullptr) {
            std::cerr << "dependency is not null but should be:\n";
            displayDependency(dependency);
            return test::Result::FAILURE;
        }
        return test::Result::SUCCESS;
    }

    test::Result testReadDependencyWithColonInDependencyName() {
        Dependency *dependency = readDependency("git https:dependency #aaax54b");
        Dependency expected = Dependency{Provider::GIT, "https:dependency", Version{VersionType::EXACT, "#aaax54b"}};
        return test::booleanToResult(compareDependencies(&expected, dependency));
    }

    test::Result testReadDependencyWithSlashInDependencyName() {
        Dependency *dependency = readDependency("git https/dependency #aaax54b");
        Dependency expected = Dependency{Provider::GIT, "https/dependency", Version{VersionType::EXACT, "#aaax54b"}};
        return test::booleanToResult(compareDependencies(&expected, dependency));
    }

    test::Result testReadDependencyWithValidUrlInDependencyName() {
        Dependency *dependency = readDependency("git https://my-domain.com/path/to/file #aaax54b");
        Dependency expected = Dependency{Provider::GIT, "https://my-domain.com/path/to/file", Version{VersionType::EXACT, "#aaax54b"}};
        return test::booleanToResult(compareDependencies(&expected, dependency));
    }

    void testDependencySolver(test::Tests *tests) {
        tests->beginTestBlock("dependency solver");
        tests->addTest(testReadDependencyWithEmptyLine, "read dependency with empty line");
        tests->addTest(testReadDependencyWithOnlyProvider, "read dependency with only provider");
        tests->addTest(testReadDependencyWithValidProvider, "read dependency with valid provider");
        tests->addTest(testReadDependencyWithInvalidProvider, "read dependency with invalid provider");
        tests->addTest(testReadDependencyWithVersion, "read dependency with version");
        tests->addTest(testReadDependencyWithoutCommitRefSharpInVersion, "read dependency without commit ref sharp in version");

        tests->beginTestBlock("allowed characters");
        tests->beginTestBlock("spaces");
        tests->addTest(testReadDependencyWithNewlineBetweenProviderAndDependency, "read dependency with newline between provider and dependency");
        tests->addTest(testReadDependencyWithNewlineBetweenDependencyAndVersion, "read dependency with newline between dependency and version");
        tests->addTest(testReadDependencyWithMultipleSpacesBetweenProviderAndDependency,
                       "read dependency with multiple spaces between provider and dependency");
        tests->addTest(testReadDependencyWithMultipleSpacesBetweenDependencyAndVersion,
                       "read dependency with multiple spaces between dependency and version");
        tests->addTest(testReadDependencyWithTabBetweenProviderAndDependency, "read dependency with tab between provider and dependency");
        tests->addTest(testReadDependencyWithTabBetweenDependencyAndVersion, "read dependency with tab between dependency and version");
        tests->addTest(testReadDependencyWithMultipleTabsBetweenProviderAndDependency,
                       "read dependency with multiple tabs between provider and dependency");
        tests->addTest(testReadDependencyWithMultipleTabsBetweenDependencyAndVersion,
                       "read dependency with multiple tabs between dependency and version");
        tests->addTest(testReadDependencyWithSpacesAndTabsBetweenProviderAndDependency,
                       "read dependency with spaces and tabs between provider and dependency");
        tests->addTest(testReadDependencyWithSpacesAndTabsBetweenDependencyAndVersion,
                       "read dependency with spaces and tabs between dependency and version");
        tests->addTest(testReadDependencyWithoutSpaceBetweenDependencyAndVersion, "read dependency without space between dependency and version");
        tests->addTest(testReadDependencyWithSpacesAfterVersion, "read dependency with spaces after version");
        tests->addTest(testReadDependencyWithSpacesAfterDependencyWithoutVersion, "read dependency with spaces after dependency without version");
        tests->addTest(testReadDependencyWithSpacesBeforeProvider, "read dependency with spaces before provider");
        tests->endTestBlock();
        tests->beginTestBlock("special characters");
        tests->addTest(testReadDependencyWithCharsAfterVersion, "read dependency with chars after version");
        tests->addTest(testReadDependencyWithSpecialCharacterInProvider, "read dependency with special character in dependency");
        tests->addTest(testReadDependencyWithSpecialCharacterInDependency, "read dependency with special character in provider");
        tests->addTest(testReadDependencyWithSpecialCharacterInVersion, "read dependency with special character in version");
        tests->addTest(testReadDependencyWithInvalidFirstProviderCharacter, "read dependency with invalid first provider character");
        tests->addTest(testReadDependencyWithColonInDependencyName, "read dependency with colon in dependency name");
        tests->addTest(testReadDependencyWithSlashInDependencyName, "read dependency with slash in dependency name");
        tests->addTest(testReadDependencyWithValidUrlInDependencyName, "read dependency with valid url in dependency name");
        tests->endTestBlock();
        tests->endTestBlock();
        tests->endTestBlock();
    }

} // namespace dependencySolverTests
