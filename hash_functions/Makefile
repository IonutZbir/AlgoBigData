# Variables
CXX = g++
CXXFLAGS = -std=c++17 -Wall

# Target executable
TARGET = main

# Default target
all: $(TARGET)

# Rule to build the target executable
$(TARGET): main.o hash_functions.o
	$(CXX) $(CXXFLAGS) -o $(TARGET) main.o hash_functions.o

# Rule to compile main.cpp
main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

# Rule to compile hash_functions.cpp
hash_functions.o: hash_functions.cpp
	$(CXX) $(CXXFLAGS) -c hash_functions.cpp -o hash_functions.o

# Run the program
run:
	./$(TARGET)

# Clean build files
clean:
	rm -f $(TARGET) main.o hash_functions.o
