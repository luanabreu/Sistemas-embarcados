#include <stdio.h>
#include <stdlib.h>
#include "bib_arqs.h"

int main(int argc, char *argv){
	
	int resultado;
	char nome_arquivo[20];

	printf("Nome do arquivo: ");
	scanf("%s",nome_arquivo);
	
	resultado = tam_arq_text(nome_arquivo);

	printf("%d\n",resultado);

	return 0;
}