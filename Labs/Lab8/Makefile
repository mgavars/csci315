
CC = gcc -I ./include
CFLAGS = -std=gnu99 -Wall -g #-DDEBUG
LFLAGS = -lm

INC = ./include
SRC = ./src
OBJ = ./obj
DOC = ./doc
BIN = ./bin

vpath %.h ./include
vpath %.c ./src

EXECS = dlisttest

all: $(EXECS)

doc:
	doxygen

$(OBJ)/dnode.o: dnode.h dnode.c
	$(CC) $(CFLAGS) -c $(SRC)/dnode.c -o $(OBJ)/dnode.o

$(OBJ)/dlist.o: dlist.h dlist.c dnode.h
	$(CC) $(CFLAGS) -c $(SRC)/dlist.c -o $(OBJ)/dlist.o

dlisttest: $(SRC)/dlisttest.c $(OBJ)/dnode.o $(OBJ)/dlist.o
	$(CC) $(CFLAGS) $(OBJ)/dnode.o $(OBJ)/dlist.o $(SRC)/dlisttest.c -o $(BIN)/dlisttest

$(OBJ)/allocator.o: allocator.h allocator.c
	$(CC) $(CFLAGS) -c $(SRC)/allocator.c -o $(OBJ)/allocator.o

memory-test: $(SRC)/memory-test.c $(OBJ)/dnode.o $(OBJ)/dlist.o $(OBJ)/allocator.o
	$(CC) $(CFLAGS) $(OBJ)/dnode.o $(OBJ)/dlist.o $(OBJ)/allocator.o $(SRC)/memory-test.c -o $(BIN)/memory-test

frag-eval: $(SRC)/frag-eval.c $(OBJ)/dnode.o $(OBJ)/dlist.o $(OBJ)/allocator.o
	$(CC) $(CFLAGS) $(OBJ)/dnode.o $(OBJ)/dlist.o $(OBJ)/allocator.o $(SRC)/frag-eval.c -o $(BIN)/frag-eval

student: $(SRC)/sfu.c $(SRC)/dfu.c $(SRC)/student.c 
	$(CC) $(CFLAGS) $(SRC)/dfu.c $(SRC)/sfu.c $(SRC)/student.c  $(LFLAGS) -o $(BIN)/student


.PHONY: clean
clean:
	/bin/rm -rf $(BIN)/* $(OBJ)/* core* *~

