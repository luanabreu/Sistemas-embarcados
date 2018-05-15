#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#define linhas 60
#define colunas 60

struct name_matrizes
{
	long int a[linhas][colunas];
	long int b[linhas][colunas];
	long int c[linhas][colunas];
}typedef matrizes;

matrizes args_threads;

void preencher(long int a[linhas][colunas], long int b[linhas][colunas]);
void mostrar(long int matriz[linhas][colunas]);

void* soma_1(void *v)
{
	int i,j;

	for (i=0;i<(linhas/3);i++)
	{
		for (j=0;j<colunas;j++)
		{
			args_threads.c[i][j] = args_threads.a[i][j] + args_threads.b[i][j];
		}
	}

	return NULL;
}

void* soma_2(void *v)
{
	int i,j;

	for (i=(linhas/3);i<(2*linhas/3);i++)
	{
		for (j=0;j<colunas;j++)
		{
			args_threads.c[i][j] = args_threads.a[i][j] + args_threads.b[i][j];
		}
	}

	return NULL;
}

void* soma_3(void *v)
{
	int i,j;

	for (i=(2*linhas/3);i<linhas;i++)
	{
		for (j=0;j<colunas;j++)
		{
			args_threads.c[i][j] = args_threads.a[i][j] + args_threads.b[i][j];
		}
	}

	return NULL;
}


int main ()
{
	int i,j;
	pthread_t thread_id[3];
	

	preencher(args_threads.a,args_threads.b);

	pthread_create(&thread_id[0],NULL,&soma_1,NULL);
	pthread_create(&thread_id[1],NULL,&soma_2,NULL);
	pthread_create(&thread_id[2],NULL,&soma_3,NULL);
	pthread_join(thread_id[0],NULL);
	pthread_join(thread_id[1],NULL);
	pthread_join(thread_id[2],NULL);

	/*
	mostrar(args_threads.a);
	printf("\n");
	mostrar(args_threads.b);
	printf("\n");
	mostrar(args_threads.c);
	printf("\n");
	*/
	
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
