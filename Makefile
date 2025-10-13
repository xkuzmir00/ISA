# Author: Richard Kuzmisin
# Login: xkuzmir00 (260077)

CXX := g++
CXXFLAGS := -Wall -std=c++20
TARGET := dns
SRCDIRS := . models utility
SRC := $(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.cpp))

.PHONY: all test clean build

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

build:
	./$(TARGET)

TEST_SRC := tests/test_argumentParser.cpp
TEST_TARGET := tests/test_runner

TEST_OBJECTS := $(filter-out ./dns.cpp, $(SRC))

test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(TEST_SRC) $(TEST_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(TEST_SRC) $(TEST_OBJECTS)

clean:
	rm -f $(TARGET) $(TEST_TARGET)