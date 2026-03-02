#ifndef DEPENDENCY_SOLVER_TESTS_HPP
#define DEPENDENCY_SOLVER_TESTS_HPP

#include "../../cpp_tests/src/tests.hpp"
#include "../../src/dependency_solver/dependency_solver.hpp"

namespace dependencySolverTests {
    void displayDependency(const Dependency *dependency);
    
    // return whether actual equals expected
    bool compareDependencies(const Dependency *expected, const Dependency *actual);

    void testDependencySolver(test::Tests *tests);
} // namespace dependencySolverTests

#endif // DEPENDENCY_SOLVER_TESTS_HPP
