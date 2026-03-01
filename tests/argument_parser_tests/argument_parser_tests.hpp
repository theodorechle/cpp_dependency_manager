#ifndef ARGUMENT_PARSER_TESTS_HPP
#define ARGUMENT_PARSER_TESTS_HPP

#include "../../cpp_tests/src/tests.hpp"
#include "../../src/argument_parser/argument_parser.hpp"

namespace argumentParserTests {
    void listArguments(const Arguments &arguments);
    bool compareArguments(const Arguments &expected, const Arguments &actual);

    void testArgumentParser(test::Tests *tests);
} // namespace argumentParserTests

#endif // ARGUMENT_PARSER_TESTS_HPP
