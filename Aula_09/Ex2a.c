#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

#define linhas 60
#define colunas 60

void preencher(long int a[linhas][colunas]);
void multi(long int a[linhas][colunas], long int b[linhas][colunas],long int res[linhas][colunas]);
void mostrar(long int matriz[linhas][colunas]);

int main ()
{
	long int a[linhas][colunas],b[linhas][colunas],res[linhas][colunas];
	int i,j;

	preencher(a);
	preencher(b);
	
	multi(a,b,res);

	mostrar(a);
	printf("\n");
	mostrar(b);
	printf("\n");
	mostrar(res);
	printf("\n");


	return 0;
}

void preencher(long int a[linhas][colunas]){

	int i,j;

	for (i = 0; i < linhas; i++)
	{
		for (j = 0; j < colunas; j++)
		{
			srandom(i+j+time(NULL));
			a[i][j] = random()%10;
		}
	}
}

void mostrar(long int matriz[linhas][colunas]){
	int i,j;

	for(i=0;i<linhas;i++){
		for (j = 0; j < colunas; j++)
		{
			printf("%ld ",matriz[i][j]);
		}

		printf("\n");
	}
}

void multi(long int a[linhas][colunas], long int b[linhas][colunas], long int res[linhas][colunas]){

	int i,j,n;

	for(i=0;i<linhas;i++){
		for(j=0;j<colunas;j++){
			res[i][j]=0;
			for(n=0;n<3;n++){

				res[i][j] += a[i][n]*b[n][j];
			}
		}
	}


}
