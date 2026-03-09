#include "argument_parser_tests.hpp"

namespace argumentParserTests {
    void listArguments(const Arguments &arguments) {
        for (std::pair<std::string, Argument> argument : arguments) {
            std::cerr << argument.first << "(" << argumentTypeToString(argument.second.type) << ")";
            if (argument.second.values.size() != 0) std::cerr << ":";
            for (std::string value : argument.second.values) {
                std::cerr << " " << value;
            }
            std::cerr << "\n";
        }
    }

    bool compareArguments(const Arguments &expected, const Arguments &actual) {
        bool equal = true;
        if (expected.size() != actual.size()) {
            std::cerr << "expected " << expected.size() << " argument";
            if (expected.size() > 1) std::cerr << "s";
            std::cerr << ", got " << actual.size() << "\n";
            equal = false;
        }
        for (std::pair<std::string, Argument> argument : expected) {
            Arguments::const_iterator actualArgument = actual.find(argument.first);
            if (actualArgument == actual.cend()) {
                std::cerr << "expected argument '" << argument.first << "'\n";
                equal = false;
            }
            else {
                if (argument.second.values.size() != actualArgument->second.values.size()) equal = false;
                else {
                    std::vector<std::string>::const_iterator actualValuesIterator = actualArgument->second.values.cbegin();
                    for (const std::string &value : argument.second.values) {
                        if (value != *actualValuesIterator) {
                            equal = false;
                            break;
                        }
                        actualValuesIterator++;
                    }
                }
                std::cerr << argument.first;
                if (argument.second.values.size() != 0) std::cerr << ":";
                for (std::string value : argument.second.values) {
                    std::cerr << " " << value;
                }
                std::cerr << "|";
                for (std::string value : actualArgument->second.values) {
                    std::cerr << " " << value;
                }
            }
        }
        for (std::pair<std::string, Argument> argument : actual) {
            Arguments::const_iterator expectedArgument = actual.find(argument.first);
            if (expectedArgument == actual.cend()) {
                std::cerr << "extra argument '" << argument.first << "'";
                if (argument.second.values.size() != 0) std::cerr << ":";
                for (std::string value : argument.second.values) {
                    std::cerr << " " << value;
                }
            }
        }
        return equal;
    }

    test::Result testNoArguments() { return test::booleanToResult(argumentParser(0, nullptr).size() == 0); }

    test::Result testNoArgumentsWithProgramName() {
        const char *initialArgs[] = {"program-name"};
        return test::booleanToResult(argumentParser(1, initialArgs).size() == 0);
    }

    test::Result testFirstArgumentWithoutDash() {
        const char *initialArgs[] = {"program-name", "test"};
        Arguments expected = {{"test", Argument{ArgumentType::NO_DASH_FIRST_ARGUMENT}}};
        Arguments parsedArgs = argumentParser(2, initialArgs);
        return test::booleanToResult(compareArguments(expected, parsedArgs));
    }

    test::Result testShortFirstArgument() {
        const char *initialArgs[] = {"program-name", "-t"};
        Arguments expected = {{"t", Argument{ArgumentType::SHORT}}};
        Arguments parsedArgs = argumentParser(2, initialArgs);
        return test::booleanToResult(compareArguments(expected, parsedArgs));
    }

    test::Result testLongFirstArgument() {
        const char *initialArgs[] = {"program-name", "--test"};
        Arguments expected = {{"test", Argument{ArgumentType::LONG}}};
        Arguments parsedArgs = argumentParser(2, initialArgs);
        return test::booleanToResult(compareArguments(expected, parsedArgs));
    }

    test::Result testFirstArgumentWithoutDashWithSingleValue() {
        const char *initialArgs[] = {"program-name", "test", "first-arg"};
        Arguments expected = {{"test", Argument{ArgumentType::NO_DASH_FIRST_ARGUMENT, {"first-arg"}}}};
        Arguments parsedArgs = argumentParser(3, initialArgs);
        return test::booleanToResult(compareArguments(expected, parsedArgs));
    }

    test::Result testShortFirstArgumentWithSingleValue() {
        const char *initialArgs[] = {"program-name", "-t", "first-arg"};
        Arguments expected = {{"t", Argument{ArgumentType::SHORT, {"first-arg"}}}};
        Arguments parsedArgs = argumentParser(3, initialArgs);
        return test::booleanToResult(compareArguments(expected, parsedArgs));
    }

    test::Result testLongFirstArgumentWithSingleValue() {
        const char *initialArgs[] = {"program-name", "--test", "first-arg"};
        Arguments expected = {{"test", Argument{ArgumentType::LONG, {"first-arg"}}}};
        Arguments parsedArgs = argumentParser(3, initialArgs);
        return test::booleanToResult(compareArguments(expected, parsedArgs));
    }

    test::Result testFirstArgumentWithoutDashWithMultipleValues() {
        const char *initialArgs[] = {"program-name", "test", "first-arg", "second-arg"};
        Arguments expected = {{"test", Argument{ArgumentType::NO_DASH_FIRST_ARGUMENT, {"first-arg", "second-arg"}}}};
        Arguments parsedArgs = argumentParser(4, initialArgs);
        return test::booleanToResult(compareArguments(expected, parsedArgs));
    }

    test::Result testShortFirstArgumentWithMultipleValues() {
        const char *initialArgs[] = {"program-name", "-t", "first-arg", "second-arg"};
        Arguments expected = {{"t", Argument{ArgumentType::SHORT, {"first-arg", "second-arg"}}}};
        Arguments parsedArgs = argumentParser(4, initialArgs);
        return test::booleanToResult(compareArguments(expected, parsedArgs));
    }

    test::Result testLongFirstArgumentWithMultipleValues() {
        const char *initialArgs[] = {"program-name", "--test", "first-arg", "second-arg"};
        Arguments expected = {{"test", Argument{ArgumentType::LONG, {"first-arg", "second-arg"}}}};
        Arguments parsedArgs = argumentParser(4, initialArgs);
        return test::booleanToResult(compareArguments(expected, parsedArgs));
    }

    test::Result testMultipleShortArguments() {
        const char *initialArgs[] = {"program-name", "-what"};
        Arguments expected = {{"w", Argument{ArgumentType::SHORT}},
                              {"h", Argument{ArgumentType::SHORT}},
                              {"a", Argument{ArgumentType::SHORT}},
                              {"t", Argument{ArgumentType::SHORT}}};
        Arguments parsedArgs = argumentParser(2, initialArgs);
        return test::booleanToResult(compareArguments(expected, parsedArgs));
    }

    test::Result testMultipleShortArgumentsWithValueForLastOne() {
        const char *initialArgs[] = {"program-name", "-what", "an-arg"};
        Arguments expected = {{"w", Argument{ArgumentType::SHORT}},
                              {"h", Argument{ArgumentType::SHORT}},
                              {"a", Argument{ArgumentType::SHORT}},
                              {"t", Argument{ArgumentType::SHORT, {"an-arg"}}}};
        Arguments parsedArgs = argumentParser(3, initialArgs);
        return test::booleanToResult(compareArguments(expected, parsedArgs));
    }

    test::Result testCombiningArgumentTypesAndValues() {
        const char *initialArgs[] = {"program-name", "first-arg", "with-value", "-r",    "arg",
                                     "--test",       "first-arg", "second-arg", "-what", "an-other-arg"};
        Arguments expected = {{"first-arg", Argument{ArgumentType::NO_DASH_FIRST_ARGUMENT, {"with-value"}}},
                              {"r", Argument{ArgumentType::SHORT, {"arg"}}},
                              {"test", Argument{ArgumentType::LONG, {"first-arg", "second-arg"}}},
                              {"w", Argument{ArgumentType::SHORT}},
                              {"h", Argument{ArgumentType::SHORT}},
                              {"a", Argument{ArgumentType::SHORT}},
                              {"t", Argument{ArgumentType::SHORT, {"an-other-arg"}}}};
        Arguments parsedArgs = argumentParser(10, initialArgs);
        return test::booleanToResult(compareArguments(expected, parsedArgs));
    }

    void testArgumentParser(test::Tests *tests) {
        tests->beginTestBlock("argument parser");
        tests->addTest(testNoArguments, "no arguments");
        tests->addTest(testFirstArgumentWithoutDash, "first argument without dash");
        tests->addTest(testShortFirstArgument, "short first argument");
        tests->addTest(testLongFirstArgument, "long first argument");
        tests->addTest(testFirstArgumentWithoutDashWithSingleValue, "first argument without dash with single value");
        tests->addTest(testShortFirstArgumentWithSingleValue, "short first argument with single value");
        tests->addTest(testLongFirstArgumentWithSingleValue, "long first argument with single value");
        tests->addTest(testFirstArgumentWithoutDashWithMultipleValues, "first argument without dash with multiple values");
        tests->addTest(testShortFirstArgumentWithMultipleValues, "short first argument with multiple values");
        tests->addTest(testLongFirstArgumentWithMultipleValues, "long first argument with multiple values");
        tests->addTest(testMultipleShortArguments, "multiple short arguments");
        tests->addTest(testMultipleShortArgumentsWithValueForLastOne, "multiple short arguments with value for last one");
        tests->addTest(testCombiningArgumentTypesAndValues, "combining argument types and values");
        tests->endTestBlock();
    }

} // namespace argumentParserTests
