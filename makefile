# Copy and adapt the contents of a makefile here.
# Use separate compilation, support "make clean", and name your 
# executable "fans" as per the specification
EXE = fans

FLAGS = -Wall -Wextra -g
# FLAGS = -Wall -O3
CC = g++
BIN = bin
OBJ = obj

# Store executables in a subdirectory
all: $(BIN)/$(EXE)

$(BIN)/$(EXE): $(OBJ)/fans.o $(OBJ)/Email.o $(OBJ)/Phone.o $(OBJ)/Fan.o $(OBJ)/LinkedList.o 
	$(CC) $(FLAGS) $(OBJ)/Email.o $(OBJ)/Phone.o $(OBJ)/Fan.o $(OBJ)/fans.o $(OBJ)/LinkedList.o  -o $@

$(OBJ)/fans.o: fans.cpp BinarySearchTree.cpp
	$(CC) -c fans.cpp -o $@

$(OBJ)/Phone.o: Phone.h
	$(CC) -c Phone.cpp -o $@

$(OBJ)/Fan.o: Fan.h
	$(CC) -c Fan.cpp -o $@

$(OBJ)/Email.o: Email.h 
	$(CC) -c Email.cpp -o $@

$(OBJ)/LinkedList.o: LinkedList.h 
	$(CC) -c LinkedList.cpp -o $@

# $(OBJ)/BinarySearchTree.o: 
# 	$(CC) -c BinarySearchTree.cpp -o $@



clean:
	rm -f $(OBJ)/*.o $(BIN)/$(EXE) *.tar.gz

