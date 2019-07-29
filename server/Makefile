CC = gcc
CFLAG = -g -pthread
PROG = server

all: $(PROG)

debug: CFLAG += -DDEBUG
debug:$(PROG)

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAG)

server: server.c def.o def.h
	$(CC) server.c -o $@ def.o $(CFLAG)
