CXX = g++
CXXFLAGS = -Wall -Wextra -O2
TARGET = main
SRC = $(wildcard *.cpp ../../helpers/*.cpp)

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)

