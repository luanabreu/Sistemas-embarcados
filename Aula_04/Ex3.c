#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
	

	FILE *fp;
	char *nome,*aux,*idade;

	nome = argv[1];
	idade = argv[2];

	sprintf(aux,"%s.txt",nome);	
	
	fp = fopen(aux,"w");

	if(!fp){
		printf("Erro ao abrir o arquivo\n");
		exit(0);
	}


	fprintf(fp,"Nome: %s\n",nome);
	fprintf(fp,"Idade: %s\n",idade);

	fclose(fp);

	return 0;
}