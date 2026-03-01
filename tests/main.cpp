#include "../cpp_tests/src/tests.hpp"
#include "argument_parser_tests/argument_parser_tests.hpp"

int main() {
    test::Tests tests = test::Tests();
    argumentParserTests::testArgumentParser(&tests);
    tests.runTests();
    tests.displaySummary();
    return !tests.allTestsPassed();
}
