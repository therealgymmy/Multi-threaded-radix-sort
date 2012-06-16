CXX=g++
CXXFLAGS=-std=c++11 -Wall -Wextra
SRC=main.cpp \
	radix.cpp \
	radix.hpp

rsort:
	$(CXX) $(CXXFLAGS) $(SRC) -o rsort.exe

.phony:
clean:
	rm rsort.exe
