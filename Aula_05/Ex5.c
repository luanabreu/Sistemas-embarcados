#include <stdio.h>
#include <stdlib.h>
#include "bib_arqs.h"

int main(int argc, char *argv){
	
	char conteudo[100];
	char nome_arquivo[20];

	printf("Nome do arquivo: ");
	scanf("%s",nome_arquivo);
	
	le_arq_texto(nome_arquivo,conteudo);

	printf("%s",conteudo);

	return 0;
}