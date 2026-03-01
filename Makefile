CPP_C=g++
CPP_FLAGS=-std=c++23 -Wall -g -MMD -MP
BIN_DIR=bin
OBJ_DIR=obj
SRC_DIR=src
TESTS_DIR=tests
TESTS_LIB=cpp_tests/bin/cpp_tests_lib

# Source files
SRC_MAIN=$(SRC_DIR)/main.cpp
OBJ_MAIN=$(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_MAIN)) 

SUBDIRS=argument_parser dependency_installer dependency_solver project_runner
SRC_SUBDIRS=$(foreach dir, $(SUBDIRS), $(wildcard $(SRC_DIR)/$(dir)/*.cpp))
OBJ=$(foreach dir, $(SUBDIRS), $(wildcard $(SRC_DIR)/$(dir)/*.cpp))

TEST_SUBDIRS=argument_parser_tests
SRC_TESTS=$(wildcard $(TESTS_DIR)/*.cpp) $(wildcard $(TESTS_DIR)/*/*.cpp)
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
	$(CPP_C) $(CPP_FLAGS) -o $@ $^

# Build the tests executable (tests + lib)
$(TESTS): $(OBJ) $(OBJ_TESTS) $(TESTS_LIB).a
	@mkdir -p $(BIN_DIR)
	$(CPP_C) $(CPP_FLAGS) -o $@ $^

# Rule for compiling all object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CPP_C) $(CPP_FLAGS) -c $< -o $@

$(TESTS_LIB).a:
	$(MAKE) -C cpp_tests -j lib DEBUG=$(DEBUG) BASH_COLORS=$(BASH_COLORS)

# Clean all generated files
clean:
	@find obj -mindepth 1 ! -name .gitkeep -delete
	@find bin -mindepth 1 ! -name .gitkeep -delete
	$(MAKE) -C cpp_tests clean
