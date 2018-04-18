#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv){
	

	FILE *fp;
	//char c [20] = "Ola Mundo!";
	int i;

	fp = fopen("ola_mundo.txt","w");

	if(!fp){
		printf("Erro ao abrir o arquivo\n");
		exit(0);
	}

	//for(i=0; c[i]; i++){
	fputs("Ola Mundo!\n", fp);
	//}

	fclose(fp);

	return 0;
}