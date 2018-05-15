#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

float media(long int *v);

int main ()
{
	
	long int v[50000];
	int i;
	float media_total;

	//criando vetor

	for(i=0;i<50000;i++){
		srandom(i+1);
		v[i] = random();
	}

	//valor da busca completa

	media_total = media(v);
	
	printf("Media por busca completa: %.2lf\n",media_total);


	return 0;
}

float media(long int *v){

	long int soma = 0;
	float media;
	int i;

	for(i=0;i<50000;i++){
		soma += v[i];	
	}
	
	media = (float)soma /50000.00;

	return media;
}

