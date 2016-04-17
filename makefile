CXX = g++
CXXFLAGS = -g -Wall -std=c++11
LDFLAGS = -lboost_system -lboost_filesystem

tests: tests.cpp utilities.cpp process.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^ -lgtest

main: main.cpp utilities.cpp process.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^

