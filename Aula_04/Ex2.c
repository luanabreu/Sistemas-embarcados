#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv){
	

	FILE *fp;
	char nome [20], aux[20];
	int idade;
	int i;

	printf("Digite seu nome: ");
	scanf("%s",nome);
	printf("Digite sua idade: ");
	scanf("%d",&idade);

	sprintf(aux,"%s.txt",nome);	

	fp = fopen(aux,"w");

	if(!fp){
		printf("Erro ao abrir o arquivo\n");
		exit(0);
	}



	fprintf(fp,"Nome: %s\n",nome);
	fprintf(fp,"Idade: %d\n",idade);

	fclose(fp);

	return 0;
}