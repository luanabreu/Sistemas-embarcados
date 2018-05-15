#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#define linhas 60
#define colunas 60

void preencher(long int a[linhas][colunas]);
void multi(long int a[linhas][colunas], long int b[linhas][colunas]);

int main ()
{
	long int a[linhas][colunas],b[linhas][colunas];
	int i,j;

	preencher(a);

	for(i=0;i<linhas;i++){
		for (j = 0; j < colunas; j++)
		{
			printf("%ld ",a[i][j]);
		}

		printf("\n");
	}

	multi(a,b);
	
	for(i=0;i<linhas;i++){
		for (j = 0; j < colunas; j++)
		{
			printf("%ld ",b[i][j]);
		}

		printf("\n");
	}
	
	return 0;
}

void preencher(long int a[linhas][colunas]){

	int i,j;

	for (i = 0; i < linhas; i++)
	{
		for (j = 0; j < colunas; j++)
		{
			srandom(i+j+1);
			a[i][j] = random()%10;
		}
	}
}


void multi(long int a[linhas][colunas], long int b[linhas][colunas]){

	int i,j;
	long int x;

	scanf("%ld",&x);

	for (i = 0; i < linhas; i++)
	{
		for (j = 0; j < colunas; j++)
		{
			b[i][j] = a[i][j]*x;
		}
	}
}
