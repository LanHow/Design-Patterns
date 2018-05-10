.PHONY: directories clean
CC=g++
CFLAGS=-std=c++11
LIBS=-lgtest -lpthread
OBJ=obj
BIN=bin
SRC=src
TEST=test

all: directories $(BIN)/ut_all

$(BIN)/ut_all: $(OBJ)/ut_main.o
	$(CC) $(CFLAGS) -o $@ $(OBJ)/ut_main.o $(LIBS)
$(OBJ)/ut_main.o: $(TEST)/ut_main.cpp $(TEST)/ut_fs.h $(TEST)/ut_iterator.h $(TEST)/ut_visitor.h $(SRC)/node.h $(SRC)/file.h $(SRC)/folder.h $(SRC)/link.h $(SRC)/exception.h $(SRC)/find.h $(SRC)/iterator.h $(SRC)/visite.h $(SRC)/find_visitor.h $(SRC)/visitor.h $(SRC)/countline_visitor.h $(SRC)/countword_visitor.h
	$(CC) $(CFLAGS) -c $< -o $@

directories:
	mkdir -p bin obj

clean:
	rm -rf $(OBJ) $(BIN)

stat:
	wc $(SRC)/*.h $(SRC)/*.cpp $(TEST)/*.h $(TEST)/*.cpp
