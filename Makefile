CXX = g++
CXXFLAGS = -std=c++17 -O3 -Wall -Wextra -Iinclude
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = .

# Target binaries
TARGET = iot_firewall
TEST_TARGET = test_runner

# Files
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))

all: $(TARGET)

# Build the main app
$(TARGET): $(OBJECTS) $(OBJ_DIR)/main.o
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/$@ $^

# Build the test runner
test: $(OBJECTS) $(OBJ_DIR)/test_bloom.o
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/$(TEST_TARGET) $^
	./$(TEST_TARGET)

# Compile source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile main and test entry points
$(OBJ_DIR)/main.o: main.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/test_bloom.o: tests/test_bloom.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR) $(TARGET) $(TEST_TARGET)

.PHONY: all clean test
