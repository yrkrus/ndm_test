CXX      := g++
CXXFLAGS := -g -Wall -std=c++17 -fdiagnostics-color=always -I. -Ilogic
TARGET   := main
SRCS     := $(wildcard *.cpp) $(wildcard logic/*.cpp)
OBJS     := $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all clean