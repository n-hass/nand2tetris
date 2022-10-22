CXX = g++
CXXFLAGS = -std=c++11 -g -Wall

.PHONY: clean

# includes go here

SRC = VMTranslator.cpp #implementation files for classes here
OBJ = $(SRC:.cpp=.o)

$(OBJ): Filestr.hpp

# ### build targets ###
all: main test

main: main.cpp $(OBJ)
	$(CXX) $(CXXFLAGS) -o main Main.cpp $(OBJ)

# ### clean targets ###
clean:
	rm -f main
	rm -rf *.dSYM
	rm -f *.o
	rm tests/*.asm