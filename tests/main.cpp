#include "../cpp_tests/src/tests.hpp"
#include "argument_parser_tests/argument_parser_tests.hpp"
#include "dependency_solver_tests/dependency_solver_tests.hpp"

int main() {
    test::Tests tests = test::Tests();
    argumentParserTests::testArgumentParser(&tests);
    dependencySolverTests::testDependencySolver(&tests);
    tests.runTests();
    tests.displaySummary();
    return !tests.allTestsPassed();
}
