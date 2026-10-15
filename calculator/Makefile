Cg = g++
CgFLAGS = -Wall -Wextra -std=c++17
TARGET = krutoy_calculator

.PHONY: all clean run

all: $(TARGET)

$(TARGET): main.cpp
	$(Cg) $(CgFLAGS) main.cpp -o $(TARGET)

clean:
	rm -f $(TARGET)

run: all
	./$(TARGET)

