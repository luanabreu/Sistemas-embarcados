#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

volatile long int maiores[4];

void* search1(void *v)
{
	long int *vetor = (long int *) v;
	int i;

	maiores[0] = vetor[0];

	for(i=0;i<12500;i++){
		if(vetor[i]>maiores[0]){
			maiores[0] = vetor[i];
		}
	}

	//sleep(1);

	return NULL;
}

void* search2(void *v)
{
	long int *vetor = (long int *) v;
	int i;

	maiores[1] = vetor[0];

	for(i=12500;i<25000;i++){
		if(vetor[i]>maiores[1]){
			maiores[1] = vetor[i];
		}
	}

	//sleep(1);

	return NULL;
}

void* search3(void *v)
{
	long int *vetor = (long int *) v;
	int i;

	maiores[2] = vetor[0];
	for(i=25000;i<37500;i++){
		if(vetor[i]>maiores[2]){
			maiores[2] = vetor[i];
		}
	}

	//sleep(1);

	return NULL;
}

void* search4(void *v)
{
	long int *vetor = (long int *) v;
	int i;

	maiores[3] = vetor[0];
	for(i=37500;i<50000;i++){
		if(vetor[i]>maiores[3]){
			maiores[3] = vetor[i];
		}
	}

	//sleep(1);

	return NULL;
}

long int maior_numero(long int *v);

int main ()
{
	pthread_t thread_id1;
	pthread_t thread_id2;
	pthread_t thread_id3;
	pthread_t thread_id4;
	
	
	long int v[50000];
	int i;
	long int max_valor;

	//criando vetor

	for(i=0;i<50000;i++){
		srandom(i+1);
		v[i] = random();
		//printf("%ld\n",v[i]);
	}

	//iniciando threads

	pthread_create(&thread_id1, NULL,&search1,v);
	pthread_create(&thread_id2, NULL,&search2,v);
	pthread_create(&thread_id3, NULL,&search3,v);
	pthread_create(&thread_id4, NULL,&search4,v);

	//comparando resultados das 4 threads

	max_valor = maiores[0];

	for (i = 0; i < 4; i++)
	{
		if(maiores[i] > max_valor){
			max_valor = maiores[i];
		}
	}

	printf("Maior valor por busca dividida: %ld\n", max_valor);


	pthread_join(thread_id4,NULL);
	pthread_join(thread_id3,NULL);
	pthread_join(thread_id2,NULL);
	pthread_join(thread_id1,NULL);

	//valor da busca completa

	max_valor = maior_numero(v);
	
	printf("Maior valor por busca completa: %ld\n",max_valor);


	return 0;
}

long int maior_numero(long int *v){

	long int max_val;
	int i;

	max_val = v[0];
	for(i=0;i<50000;i++){
		if(v[i] > max_val){
			max_val = v[i];
		}
	}

	return max_val;
}

