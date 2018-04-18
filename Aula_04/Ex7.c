#include <stdio.h>
#include <stdlib.h>
#include "bib_arqs.h"

int main(int argc, char **argv){
	
	int ocorrencia;
	char nome_arquivo[20];
	char palavra_chave[20];

	sprintf(palavra_chave,"%s",argv[1]);
	sprintf(nome_arquivo,"%s",argv[2]);

	ocorrencia = grep_false(nome_arquivo,palavra_chave);

	printf("%d\n",ocorrencia);

	return 0;
}