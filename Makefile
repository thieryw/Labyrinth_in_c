.PHONY: all clean debug test valgrind

all: bin bin/main

test: all
	bin/main test

debug: all
	ddd bin/main test

valgrind: all
	valgrind --leak-check=full bin/main test


_OBJS = functions.o

#OBJS = bin/functions.o
OBJS = $(patsubst %,bin/%,$(_OBJS))

bin/main: bin/main.o $(OBJS)
	gcc $+ -o $@ 

bin/main.o: src/main.c $(OBJS)
	gcc -g -std=c99 -c $< -o $@ 

bin/%.o: src/%.c src/%.h
	gcc -g -std=c99 -c $< -o $@ 

bin: 
	mkdir -p bin

clean: 
	rm -r bin