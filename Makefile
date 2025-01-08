# Compiler settings
C_VERSION = c99
CC = cc
WARNINGS = -Wall -Wextra -pedantic
C_FLAGS = -std=$(C_VERSION) -O2 -g $(WARNINGS)

# Program name
PROGRAM = bin

# File discovery
HEADERS := $(shell find . -name "*.h")
MAIN_C := main.c
TESTS_C := $(shell find . -name "*_test.c")
SOURCES_C := $(shell find . -name "*.c" ! -name "*_test.c" ! -name $(MAIN_C))
ALL_C := $(MAIN_C) $(TESTS_C) $(SOURCES_C)

# Object files
MAIN_O := $(MAIN_C:.c=.o)
TESTS_O := $(TESTS_C:.c=.o)
SOURCES_O := $(SOURCES_C:.c=.o)
ALL_O := $(ALL_C:.c=.o)

# Test binaries
TESTS_BIN := $(TESTS_C:.c=)

# Default target
all: $(PROGRAM)

# Compile object files
%.o: %.c
	@echo "Compiling $<..."
	$(CC) $(C_FLAGS) -c $< -o $@

# Build main binary
$(PROGRAM): $(MAIN_O) $(SOURCES_O)
	@echo "Linking $(PROGRAM)..."
	$(CC) $(C_FLAGS) -o $(PROGRAM) $(MAIN_O) $(SOURCES_O)

# Run the program
run: $(PROGRAM)
	@echo "Running $(PROGRAM)..."
	./$(PROGRAM)

# Clean build files
clean:
	@echo "Cleaning build files..."
	rm -f $(PROGRAM) $(ALL_O) $(TESTS_BIN) a.out

# Lint the code
LINT_FLAGS = -linux
LINT_BACKUPS := $(ALL_C:.c=.c~) $(HEADERS:.h=.h~)
lint:
	@echo "Linting source files..."
	gindent $(LINT_FLAGS) $(ALL_C) $(HEADERS)
	rm -f $(LINT_BACKUPS)

# Unit testing
%_test: %_test.o $(SOURCES_O)
	@echo "Building and running test $*..."
	$(CC) $(C_FLAGS) -o $*_test $*_test.o $(SOURCES_O)
	./$*_test

# Run all test
test: $(TESTS_BIN)
	@echo "Testing..."

# Prevent deletion of intermediate files
.PRECIOUS: %.o

# Phony targets
.PHONY: all run clean lint