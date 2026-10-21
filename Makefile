CXX      := g++
CXXFLAGS := -g -Wall -std=c++17 -fdiagnostics-color=always -I. -Ilogic
LDLIBS   := -lstdc++fs

TARGET   := main
SRCS     := $(wildcard *.cpp) $(wildcard logic/*.cpp)
OBJS     := $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@ $(LDLIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# --- Тесты ---
TEST_TARGET := run_tests
TEST_SRCS   := tests/test_main.cpp logic/rule_table.cpp common.cpp log.cpp
TEST_OBJS   := $(TEST_SRCS:.cpp=.o)

test: $(TEST_TARGET)
	@./$(TEST_TARGET)

$(TEST_TARGET): $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) $(TEST_OBJS) -o $@ $(LDLIBS)

clean:
	rm -f $(TARGET) $(OBJS) $(TEST_TARGET) $(TEST_OBJS)

.PHONY: all test clean