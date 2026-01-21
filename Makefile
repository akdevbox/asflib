CC = clang
CFLAGS = -Wall -g -D_DEBUG

SRC_H := $(wildcard src/*.h)
SRC_O := $(SRC_H:.h=.o)

# main.c is supposed to be a file that you may create in this repo to experiment
main: main.o $(SRC_O)
	$(CC) $(CFLAGS) -o $@ $^
main.o: main.c
	$(CC) $(CFLAGS) -c -o $@ $<

src/%.o: src/%.h
	$(CC) $(CFLAGS) -x c -c -DASF_IMPL -Wno-pragma-once-outside-header -Wno-unused-function -o $@ $<

run: main
	./main

clean:
	rm -f src/*.o main.exe main main.o