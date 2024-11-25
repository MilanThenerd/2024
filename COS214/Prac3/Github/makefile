# Define the C++ compiler to use
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -std=c++17 -fprofile-arcs -ftest-coverage

# The binary name
TARGET = main

# List of source files (recursive search)
SOURCES := $(shell find . -type f -name "*.cpp")

# The object files
OBJECTS := $(SOURCES:.cpp=.o)

build: clean
	$(CXX) $(CXXFLAGS) $(SOURCES) -o BattleGame

all: build # $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)
	rm -rf *.so *.gcno *.gcda *.gcov lcov-report gcovr-report BattleGame

run: clean all
	clear
	./BattleGame

demo: clean all
	clear
	./BattleGame demo

coverage: clean run
	gcov main.cpp

report: coverage
	mkdir gcovr-report
	gcovr --root . --html --html-details --output gcovr-report/coverage.html
