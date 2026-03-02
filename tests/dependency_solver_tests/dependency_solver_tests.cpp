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

    void testDependencySolver(test::Tests *tests) {
        tests->beginTestBlock("dependency solver");
        tests->addTest(testReadDependencyWithEmptyLine, "read dependency with empty line");
        tests->addTest(testReadDependencyWithOnlyProvider, "read dependency with only provider");
        tests->addTest(testReadDependencyWithValidProvider, "read dependency with valid provider");
        tests->addTest(testReadDependencyWithInvalidProvider, "read dependency with invalid provider");
        tests->addTest(testReadDependencyWithVersion, "read dependency with version");
        // TODO: add tests about which characters are allowed for each field; 
        tests->endTestBlock();
    }

} // namespace dependencySolverTests
