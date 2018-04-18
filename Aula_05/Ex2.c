#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv){

	int fp;
	int cStatus;
	int wStatus;
	char nome[100];
	char aux[30];
	int idade;
	char aux_id[30];


	printf("Digite seu nome: ");
	scanf("%s",nome);
	printf("Digite sua idade: ");
	scanf("%d",&idade);
	
	sprintf(aux,"%s.txt",nome);

	fp = open(aux,O_RDWR|O_CREAT,400);

	sprintf(aux,"Nome: %s\n",nome);

	wStatus = write(fp,&aux,sizeof(aux)-1);

	sprintf(aux_id,"Idade: %d\n",idade);

	wStatus = write(fp,&aux_id,sizeof(aux_id)-1);
	
	cStatus = close(fp);
	
	return 0;
}