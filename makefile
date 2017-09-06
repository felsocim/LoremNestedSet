CC = gcc
CFLAGS = -Wall -Werror -Wextra -g
RM = rm -f

lorem: src/lorem.c node
	$(CC) $(CFLAGS) src/lorem.c obj/node.o -o bin/lorem

node: include/node.h src/node.c
	$(CC) -c src/node.c -o obj/node.o
	
clean:
	$(RM) obj/* bin/* *.stackdump

