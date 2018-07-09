#the compiler: gcc for C program, define as g++ for C++
CC = g++

  # compiler flags:
  #  -g    adds debugging information to the executable file
  #  -Wall turns on most, but not all, compiler warnings
CFLAGS = -O0
LIBS = -lstdc++ -lfftw3 -lm

  # the build target executable:
SOURCE = 1DHeat.cpp
TARGET = Heat

all: $(TARGET)

$(TARGET): $(SOURCE) functions.o
	$(CC) -o $(TARGET).o $(SOURCE) functions.o $(CFLAGS) $(LIBS)

functions.o:functions.cpp
	$(CC) -c functions.cpp $(CFLAGS) $(LIBS)

	
clean:
	rm *.o Heatdata*
