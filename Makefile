# Compiler to use
CXX = g++

# Flags to pass to the compiler
CXXFLAGS = -Wall -Wextra

# Source files
SOURCES = main.cpp order.cpp order_book.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Executable name
TARGET = trading_engine

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJECTS)

