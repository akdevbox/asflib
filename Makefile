CC = clang
CFLAGS = -Wall -g -D_DEBUG -O0

SRC_C := $(wildcard src/*.c)
SRC_O := $(SRC_C:.c=.o)

# main.c is supposed to be a file that you may create in this repo to experiment
main: main.o $(SRC_O)
	$(CC) $(CFLAGS) -o $@ $^
main.o: main.c
	$(CC) $(CFLAGS) -c -o $@ $<

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

run: main
	./main

clean:
	rm -f src/*.o main.exe main main.o
