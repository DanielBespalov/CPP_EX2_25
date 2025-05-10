CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -g

.PHONY: Main test valgrind clean

Main: main.cpp SquareMat.cpp SquareMat.hpp
	$(CXX) $(CXXFLAGS) main.cpp SquareMat.cpp -o Main
	./Main

test: test.cpp SquareMat.cpp SquareMat.hpp doctest.h
	$(CXX) $(CXXFLAGS) test.cpp SquareMat.cpp -o test
	./test

valgrind: test
	valgrind --leak-check=full ./test

clean:
	rm -f Main test
