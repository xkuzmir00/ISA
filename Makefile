# Author: Richard Kuzmisin
# Login: xkuzmir00 (260077)

CXX := g++
CXXFLAGS := -Wall -std=c++20
TARGET := dns
SRCDIRS := . models utility
SRC := $(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.cpp))

.PHONY: test clean

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

build:
	$(TARGET)

test:
	@echo "No tests implemented yet."

clean:
	rm -f $(TARGET)
