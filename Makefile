C_VERSION = c99
CC = cc
WARNINGS = -Wall -Wextra -pedantic
C_FLAGS = -std=$(C_VERSION) -O2 -g $(WARNINGS)
PROGRAM = bin
LINT_FLAGS = -linux

# Find all source files recursively in the current directory and subdirectories
SOURCES := $(shell find . -name "*.c")
HEADERS := $(shell find . -name "*.h")
OBJECTS := $(SOURCES:.c=.o)
LINT_BACKUPS := $(SOURCES:.c=.c~) $(HEADERS:.h=.h~)

all: $(PROGRAM)

# Build and Run code
run: $(PROGRAM)
	./$(PROGRAM)

# Build binary
$(PROGRAM): $(OBJECTS)
	$(CC) $(C_FLAGS) -o $(PROGRAM) $(OBJECTS)

# Build object
%.o: %.c
	$(CC) $(C_FLAGS) -c $< -o $@

# Clean build
clean:
	rm -f $(PROGRAM) $(OBJECTS) a.out

# Lint code
lint:
	gindent $(LINT_FLAGS) $(SOURCES) $(HEADERS)
	rm -f $(LINT_BACKUPS)

# Phony targets
.PHONY: all run clean lint
