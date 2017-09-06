CC = gcc
CFLAGS = -Wall -Werror -Wextra -g
RM = rm -f

lnt: src/main.c lorem node
	$(CC) $(CFLAGS) src/main.c obj/lorem.o obj/node.o -o bin/lnt

lorem: include/lorem.h src/lorem.c
	$(CC) -c src/lorem.c -o obj/lorem.o

node: include/node.h src/node.c
	$(CC) -c src/node.c -o obj/node.o
	
clean:
	$(RM) obj/* bin/* *.stackdump

