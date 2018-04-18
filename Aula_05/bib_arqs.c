#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "bib_arqs.h"

int tam_arq_text(char *nome_arquivo){

	int fp;
	int cStatus;
	char aux[20];
	int i=0;
	char buf;

	sprintf(aux,"%s.txt",nome_arquivo);	

	fp = open(aux,O_RDWR|O_CREAT,400);

	while(read(fp,&buf,sizeof(char))!=0){
		i++;
	}

	cStatus = close(fp);
	
	return i-1;
}

void le_arq_texto(char *nome_arquivo, char *conteudo){

	int fp;
	int cStatus;
	char aux[20];
	char buf;

	sprintf(aux,"%s.txt",nome_arquivo);	

	fp = open(aux,O_RDWR|O_CREAT,400);

	while(read(fp,&buf,sizeof(char))!=0){
		printf("%c",buf);
	}

	cStatus = close(fp);
}

int grep_false(char *nome_arquivo, char *palavra_chave){

	int fp;
	int cStatus;
	char aux[20];
	char p_chave[100];
	char buf[100];
	int i=0;
	int igual;
	int ocorrencia=0;

	sprintf(aux,"%s.txt",nome_arquivo);	
	sprintf(p_chave,"%s",palavra_chave);	

	//printf("%ld\n",sizeof(palavra_chave));

	fp = open(aux,O_RDWR|O_CREAT,400);

	while(read(fp,&buf[i],sizeof(char))!=0){
		printf("%c\n",buf[i]);
		i++;
	}

	cStatus = close(fp);

	return ocorrencia;

}