#include "../cpp_tests/src/tests.hpp"

int main() {
    test::Tests tests = test::Tests();
    tests.runTests();
    tests.displaySummary();
    return !tests.allTestsPassed();
}
