CC = gcc
CFLAGS = -Wall -Werror -Wextra -g
RM = rm -f

lnt: src/main.c shared node
	$(CC) $(CFLAGS) src/main.c obj/shared.o obj/node.o -o bin/lnt

node: include/node.h include/shared.h src/node.c
	$(CC) -c src/node.c -o obj/node.o
	
shared: include/shared.h src/shared.c
	$(CC) -c src/shared.c -o obj/shared.o
	
clean:
	$(RM) obj/* bin/* *.stackdump
