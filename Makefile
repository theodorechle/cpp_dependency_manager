CPP_C=g++
CPP_FLAGS=-std=c++23 -Wall -g -MMD -MP
DEPENDENCIES=-lgit2
BIN_DIR=bin
OBJ_DIR=obj/src
OBJ_TEST_DIR=obj/test
SRC_DIR=src
TESTS_DIR=tests
TESTS_LIB=cpp_tests/bin/cpp_tests_lib

# Source files
SRC_MAIN=$(SRC_DIR)/main.cpp
OBJ_MAIN=$(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_MAIN)) 

SUBDIRS=argument_parser dependency_installer dependency_solver project_runner models commands_executor help dependency_installer/abstract_installer dependency_installer/git_installer
SRC_SUBDIRS=$(foreach dir, $(SUBDIRS), $(wildcard $(SRC_DIR)/$(dir)/*.cpp))
OBJ=$(foreach dir, $(SUBDIRS), $(wildcard $(SRC_DIR)/$(dir)/*.cpp))

# Source files
TEST_MAIN=$(TESTS_DIR)/main.cpp
TEST_OBJ_MAIN=$(patsubst $(TESTS_DIR)/%.cpp, $(OBJ_TEST_DIR)/%.o, $(TEST_MAIN)) 

TEST_SUBDIRS=argument_parser_tests dependency_solver_tests
SRC_TESTS=$(foreach dir, $(TEST_SUBDIRS), $(wildcard $(TESTS_DIR)/$(dir)/*.cpp))
OBJ_TESTS=$(patsubst $(SRC_DIR)/%.cpp, $(OBJ_TEST_DIR)/%.o, $(SRC_TESTS))

# Executable targets
MAIN=$(BIN_DIR)/dependency_manager
TESTS=$(BIN_DIR)/tests

.PHONY: all clean tests

ifeq ($(DEBUG),1)
CPP_FLAGS += -DDEBUG
endif

all: $(MAIN)

tests: $(TESTS)

# Build everything except tests
$(MAIN): $(OBJ) $(OBJ_MAIN)
	@mkdir -p $(BIN_DIR)
	$(CPP_C) $(CPP_FLAGS) -o $@ $^ $(DEPENDENCIES)

# Build the tests executable (tests + lib)
$(TESTS): $(OBJ) $(OBJ_TESTS) $(TESTS_LIB).a $(TEST_OBJ_MAIN)
	@mkdir -p $(BIN_DIR)
	$(CPP_C) $(CPP_FLAGS) -o $@ $^ $(DEPENDENCIES)

# Rule for compiling all object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CPP_C) $(CPP_FLAGS) -c $< -o $@

# Rule for compiling all object files
$(OBJ_TEST_DIR)/%.o: $(TESTS_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CPP_C) $(CPP_FLAGS) -c $< -o $@

$(TESTS_LIB).a:
	$(MAKE) -C cpp_tests -j lib DEBUG=$(DEBUG) BASH_COLORS=$(BASH_COLORS)

# Clean all generated files
clean:
	@find obj -mindepth 1 ! -name .gitkeep -delete
	@find bin -mindepth 1 ! -name .gitkeep -delete
	$(MAKE) -C cpp_tests clean
