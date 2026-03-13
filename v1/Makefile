CXX = g++
CXXFLAGS = -Wall -std=c++17 -Iinclude
# Leave LIBS empty for standard C++ projects
LIBS = 
TARGET = brainfuck

SRC_DIR = src
OBJ_DIR = obj

# Find all .cpp files in the src directory
SRC = $(shell find $(SRC_DIR) -type f -name '*.cpp')

# Substitute the 'src/' prefix with 'obj/' and '.cpp' with '.o'
OBJ = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC))

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ) $(LIBS)

# Rule to compile .cpp into .o, creating necessary obj/ subdirectories on the fly
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET)
