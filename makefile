CXX=g++
CXXFLAGS=-std=c++11 -Wall -Wextra
SRC=main.cpp \
	radix.cpp \
	radix.hpp
EXEC=rsort

rsort:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(EXEC)

.phony:
clean:
	rm $(EXEC)
