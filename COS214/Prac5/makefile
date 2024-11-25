CXX = g++
CXXFLAGS = -Wall -fprofile-arcs -ftest-coverage -std=c++17

TARGET = Game
SOURCES = $(wildcard *.cpp) # Use wildcard to gather .cpp files
OBJECTS = $(SOURCES:.cpp=.o)

LIBS = # Define any common libraries here (e.g., -lm)

all: $(TARGET)

# Link the executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS) $(LIBS)

# Compile each source file into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(OBJECTS) $(TARGET) *.gcda *.gcno

# Run the game without GUI
run: clean all
	./$(TARGET)

# Run the game with GUI (SFML)
demo: clean
	./$(TARGET)

.PHONY: all clean run demo

# Generate the coverage report
coverage: clean all
	./$(TARGET)
	gcovr --root . --exclude-unreachable-branches --exclude-throw-branches --xml -o coverage.xml
	gcovr --root . --html --html-details --output coverage.html

# Create an HTML report for coverage
report: coverage
	rm -rf gcovr-report
	mkdir gcovr-report
	gcovr --root . --html --html-details --output gcovr-report/coverage.html

valgrind: all
	valgrind --leak-check=full --track-origins=yes ./$(TARGET)
