# Mitch Gavars
# Prof. Marchiori
# CSCI 315 Lab 0
# 8/27/19

CC = gcc
CFLAGS = -std=gnu99 -Wall -g #-DDEBUG

EXECS = dlisttest

all: $(EXECS)

dnode.o: dnode.c dnode.h
	$(CC) $(CFLAGS) dnode.c -c -o dnode.o 

dlist.o: dlist.h dlist.c dnode.h
	$(CC) $(CFLAGS) dlist.c -c -o dlist.o 

dlisttest: dlisttest.c dnode.o dlist.o
	$(CC) $(CFLAGS) dlisttest.c dnode.o dlist.o -o dlisttest 

.PHONY: clean
clean:
	/bin/rm -rf $(EXECS) dnode.o dlist.o

