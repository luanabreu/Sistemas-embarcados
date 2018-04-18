#include <stdio.h>
#include "num_caracs.h"

int main(int argc, char **argv){

	int i = 0;
	int total = 0;

	while(i!=argc){
		total += num_caracs(argv[i]);
		i++;
	}

	printf("Total de caracteres de entrada: %d\n", total);
	
	
	return 0;
}