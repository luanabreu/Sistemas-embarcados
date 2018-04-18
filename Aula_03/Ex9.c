#include <stdio.h>
#include "num_caracs.h"

int main(int argc, char **argv){

	int i = 0;

	while(i!=argc){
		printf("Argumento: %s // Numero de caracteres: %d\n",argv[i],num_caracs(argv[i]));
		i++;
	}
	
	
	return 0;
}