#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#define linhas 60
#define colunas 60

void preencher(long int a[linhas][colunas], long int b[linhas][colunas]);
void somar(long int a[linhas][colunas], long int b[linhas][colunas], long int res[linhas][colunas]);

int main ()
{
	long int a[linhas][colunas],b[linhas][colunas],res[linhas][colunas];
	int i,j;

	preencher(a,b);

	somar(a,b,res);
	
	for(i=0;i<linhas;i++){
		for (j = 0; j < colunas; j++)
		{
			printf("%ld ",res[i][j]);
		}

		printf("\n");
	}


	
	return 0;
}

void preencher(long int a[linhas][colunas], long int b[linhas][colunas]){

	int i,j;

	for (i = 0; i < linhas; i++)
	{
		for (j = 0; j < colunas; j++)
		{
			srandom(i+j+1);
			a[i][j] = random()%10;
			b[j][i] = random()%10;
		}
	}
}


void somar(long int a[linhas][colunas], long int b[linhas][colunas],long int res[linhas][colunas]){

	int i,j;

	for (i = 0; i < linhas; i++)
	{
		for (j = 0; j < colunas; j++)
		{
			res[i][j] = a[i][j] + b[i][j];
		}
	}
}
