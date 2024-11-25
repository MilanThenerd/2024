# Variables
CC = g++
CFLAGS = -Wall -std=c++11
OBJ = main.o Menu.o Course.o MenuItem.o Starter.o MainCourse.o Dessert.o
TARGET = main

# Rules
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

main.o: main.cpp Menu.h Course.h MenuItem.h Starter.h MainCourse.h Dessert.h
	$(CC) $(CFLAGS) -c main.cpp

Menu.o: Menu.cpp Menu.h Course.h MenuItem.h Starter.h MainCourse.h Dessert.h
	$(CC) $(CFLAGS) -c Menu.cpp

Course.o: Course.cpp Course.h MenuItem.h
	$(CC) $(CFLAGS) -c Course.cpp

MenuItem.o: MenuItem.cpp MenuItem.h
	$(CC) $(CFLAGS) -c MenuItem.cpp

Starter.o: Starter.cpp Starter.h Course.h
	$(CC) $(CFLAGS) -c Starter.cpp

MainCourse.o: MainCourse.cpp MainCourse.h Course.h
	$(CC) $(CFLAGS) -c MainCourse.cpp

Dessert.o: Dessert.cpp Dessert.h Course.h
	$(CC) $(CFLAGS) -c Dessert.cpp

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)

valgrind: $(TARGET)
	valgrind --leak-check=full --show-reachable=yes ./$(TARGET)

.PHONY: all clean run valgrind
