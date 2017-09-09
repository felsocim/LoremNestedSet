# Lorem Nested Set project's makefile
# By Marek Felsoci.
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g
RM = rm -f

lnt: src/main.c shared node bin
	$(CC) $(CFLAGS) src/main.c obj/shared.o obj/node.o -o bin/lnt

node: include/node.h include/shared.h src/node.c obj
	$(CC) -c src/node.c -o obj/node.o
	
shared: include/shared.h src/shared.c obj
	$(CC) -c src/shared.c -o obj/shared.o
	
obj:
	[ -d obj ] || mkdir obj
	
bin:
	[ -d bin ] || mkdir bin

clean:
	$(RM) obj/* bin/* *.stackdump
