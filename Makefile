CXX = g++
CXXFLAGS = -std=c++17 -O2 -pthread -Iinclude

all: main benchmark

main:
	$(CXX) $(CXXFLAGS) src/main.cpp -o main

benchmark:
	$(CXX) $(CXXFLAGS) benchmarks/benchmark.cpp -o benchmark

clean:
	rm -f main benchmark

compare:
	$(CXX) $(CXXFLAGS) benchmarks/compare.cpp -o compare