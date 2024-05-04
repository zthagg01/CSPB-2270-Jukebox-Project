# Compiler Setting
GCC = g++

# Compiler Flags
FLAGS = -std=c++11 -Wall -g

# Main program executable name
TARGET = a.out

# Source directory
SRC_DIR = src

# Object directory
OBJ_DIR = obj

# Source Files
SRC = $(wildcard $(SRC_DIR)/*.cpp)

# Object Files (replacement pattern for source directory to object directory)
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Default target
all: $(TARGET)

# Link the program
$(TARGET): $(OBJ)
	$(GCC) -o $@ $^

# Rule to compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(GCC) $(FLAGS) -c $< -o $@

# Clean rule to remove generated files
clean: 
	rm -f $(TARGET) $(OBJ_DIR)/*.o *.gch *.log

# Rule to run the program
run: 
	./$(TARGET) 1

# Rule for running a specific test case
test3: 
	./$(TARGET) 1 < tests/t3.txt 

.PHONY: all clean run test3

