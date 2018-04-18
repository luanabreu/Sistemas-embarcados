#include <stdio.h>
#include <stdlib.h>
#include "bib_arqs.h"

int tam_arq_text(char *nome_arquivo){
	int i = 0;

	FILE *fp;
	char *nome = nome_arquivo;

	fp = fopen(nome,"r");

	while(getc(fp)!=EOF){
		i++;
	}

	fclose(fp);

	return i;
}

void le_arq_texto(char *nome_arquivo, char *conteudo){

	FILE *fp;
	char *nome = nome_arquivo;

	int i = 0, tamanho;

	fp = fopen(nome,"r");

	fseek(fp,0,SEEK_END);
	tamanho = ftell(fp);
	rewind(fp);

	for(i=0;i<tamanho;i++){
		conteudo[i] = getc(fp);
	}

	fclose(fp);
}

int grep_false(char *nome_arquivo, char *palavra_chave){

	FILE *fp;
	char *nome = nome_arquivo;

	int i = 0, tamanho;
	int n = 0;

	fp = fopen(nome,"r");

	fseek(fp,0,SEEK_END);
	tamanho = ftell(fp);
	rewind(fp);

	for(i=0;i<tamanho;i++){
		if(getc(fp)==palavra_chave[1]){
			if(getc(fp) == palavra_chave[2]){
				if(getc(fp) == palavra_chave[3]){
					n++;
				}
			}
		}
		
	}

	fclose(fp);

	return n;
}