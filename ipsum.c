#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

#define LEVELS 3
#define LOREM_IPSUM "loremIpsum.txt"
#define MAXIMUM 5

char * nacitaj_lorem_ipsum() {
	int fd;
	
	if((fd = open(LOREM_IPSUM, O_RDONLY)) < 0) {
		printf("Chyba pri otváraní súboru s obsahom Lorem Ipsum textu!\n");
		exit(-1);
	}
	
	struct stat buf;
	
	if(fstat(fd, &buf) < 0 ){
		printf("Chyba pri čítaní informácií o súbore s obsahom Lorem Ipsum textu!\n");
		exit(-1);
	}
	
	int size = (int) buf.st_size;
	
	char * text = (char *) malloc(size * sizeof(char));
	
	if(text == NULL) {
		printf("Chyba pamäte!\n");
		exit(-1);
	}
	
	if(read(fd, text, size) < 0) {
		printf("Chyba pri čítaní obsahu súboru Lorem Ipsum!\n");
		exit(-1);
	}
	
	return text;
}

void generovat_strom(int uroven, int predosly_pocet) {
	if(uroven == LEVELS)
		return;
		
	int nahodne = predosly_pocet + (rand() % MAXIMUM);
	int i = 0;
	
	if(nahodne < predosly_pocet)
		nahodne = predosly_pocet;
		
	if(nahodne < 1)
		nahodne = 3;
		
	//printf("Náhodné číslo: %d\n", nahodne);
	
	for(i = 0; i < nahodne; i++) {
		int j = 0;
		for(j = 0; j < uroven; j++) {
			printf("\t");
		}
		printf("Lorem ipsum dolor sit amet.\n");
		generovat_strom(uroven + 1, nahodne);
	}	
}

int main(void) {
	printf("Skúšobné spustenie započaté.\n\n");
	
	generovat_strom(0, 0);
	
	printf("\nSkúšobné spustenie ukončené.\n");
	
	return 0;
}
