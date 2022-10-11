CXX = clang++
CXXFLAGS = -std=c++11 -g -Wall

# includes go here

SRC = Assembler.cpp SymbolTable.cpp #all source files here
OBJ = $(SRC:.cpp=.o)

# ### build targets ###
Main: $(OBJ) main.cpp
	$(CXX) $(CXXFLAGS) -o main Main.cpp $(OBJ)

test: $(OBJ) test.cpp
	$(CXX) $(CXXFLAGS) -o test test.cpp $(OBJ)

# ### clean targets ###
clean:
	rm -f main test
	rm -f *.o
	rm -rf *.dSYM