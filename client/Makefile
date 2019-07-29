CC = gcc
PROG = client
CFLAG = -g

all: $(PROG)

debug: CFLAG += -DDEBUG
debug: $(PROG)

%: %.c
	$(CC)  $< -o $@ $(CFLAG)
