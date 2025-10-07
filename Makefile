# Author: Richard Kuzmisin
# Login: xkuzmir00 (260077)


CXX := g++
CXXFLAGS := -Wall -std=c++20
TARGET := dns
SRC := dns.cpp models/arguments.cpp

.PHONY: test clean

# Default: compile and run
all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

build:
	$(TARGET)

test:
	@echo "No tests implemented yet."

clean:
	rm -f $(TARGET)
