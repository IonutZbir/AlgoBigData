# Variables
CXX = g++
CXXFLAGS = -std=c++17 -Wall

# Target executable
TARGET = jaccard

# Default target
all: $(TARGET)

# Rule to build the target
$(TARGET): jaccard.o
	$(CXX) $(CXXFLAGS) -o $(TARGET) jaccard.o

# Rule to build the object file
jaccard.o: minhash/jaccard.cpp
	$(CXX) $(CXXFLAGS) -c minhash/jaccard.cpp -o jaccard.o

# Run the program with arguments
run:
	./$(TARGET) $(ARGS)

# Clean build files
clean:
	rm -f $(TARGET) jaccard.o
