#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>


int main(int argc, char **argv){
	
	int fp;
	int cStatus;
	int wStatus;
	char *nome;
	char aux[20];
	char *idade;
	char aux_id[20];

	nome = argv[1];
	idade = argv[2];

	sprintf(aux,"%s.txt",nome);	
	
	fp = open(aux,O_RDWR|O_CREAT,400);

	sprintf(aux,"Nome: %s\n",nome);

	wStatus = write(fp,&aux,sizeof(aux)-1);

	sprintf(aux_id,"Idade: %s\n",idade);

	wStatus = write(fp,&aux_id,sizeof(aux_id)-1);
	
	cStatus = close(fp);
	
	return 0;
}