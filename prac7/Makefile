CXX = g++
CXXFLAGS = -std=c++11 -g -Wall

.PHONY: clean

# includes go here

SRC = CompilerParser.cpp ParseTree.cpp Token.cpp#implementation files for classes here
OBJ = $(SRC:.cpp=.o)

# ### build targets ###
all: main

main: main.cpp $(OBJ)
	$(CXX) $(CXXFLAGS) -o main Main.cpp $(OBJ)

# ### clean targets ###
clean:
	rm -f main test
	rm -rf *.dSYM
	rm -f *.o