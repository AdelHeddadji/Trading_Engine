# This is a simple Makefile for compiling a C++ "Hello, World!" program

# Compiler to use
CXX = g++

# Flags to pass to the compiler
CXXFLAGS = -Wall -Wextra

# Executable name
TARGET = trading_engine

all: $(TARGET)

$(TARGET): main.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) main.cpp

clean:
	rm -f $(TARGET)
