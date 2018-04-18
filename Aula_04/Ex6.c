#include <stdio.h>
#include <stdlib.h>
#include "bib_arqs.h"

int main(int argc, char **argv){
	
	char conteudo[100];
	char nome_arquivo[20];

	sprintf(nome_arquivo,"%s",argv[1]);
	
	le_arq_texto(nome_arquivo,conteudo);

	printf("%s",conteudo);

	return 0;
}