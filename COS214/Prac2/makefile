# Define the C++ compiler to use
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -std=c++17 -fprofile-arcs -ftest-coverage

# The binary name
TARGET = Game

# List of source files
SOURCES = $(wildcard *.cpp)

# The object files
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)
	rm -rf *.so *.gcno *.gcda *.gcov lcov-report gcovr-report

run: all
	./Game

coverage: clean run
	gcov TestingMain.cpp

report: coverage ## Generate gcovr report
	mkdir gcovr-report
	gcovr --root . --html --html-details --output gcovr-report/coverage.html

valgrind: 
