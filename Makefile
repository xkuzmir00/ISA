CXX := g++
CXXFLAGS := -Wall -std=c++20
TARGET := Build/dns
SRC := dns.cpp

.PHONY: all run test clean

# Default: compile and run
all: $(TARGET) run

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

run:
	./$(TARGET)

test:
	@echo "No tests implemented yet."

clean:
	rm -f $(TARGET)
