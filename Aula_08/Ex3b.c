#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

volatile float medias_part[4] = {0,0,0,0};

void* search1(void *v)
{
	float *vetor = (float *) v;
	int i;

	for(i=0;i<12500;i++){
		medias_part[0] += vetor[i];
	}

	medias_part[0] = medias_part[0]/12500;

	return NULL;
}

void* search2(void *v)
{
	float *vetor = (float *) v;
	int i;

	for(i=12500;i<25000;i++){
		medias_part[1] += vetor[i];
	}

	medias_part[1] = medias_part[1]/12500;

	return NULL;
}

void* search3(void *v)
{
	float *vetor = (float *) v;
	int i;

	for(i=25000;i<37500;i++){
		medias_part[2] += vetor[i];
	}

	medias_part[2] = medias_part[2]/12500;
	
	return NULL;
}

void* search4(void *v)
{
	float *vetor = (float *) v;
	int i;

	for(i=37500;i<50000;i++){
		medias_part[3] += vetor[i];
	}

	medias_part[3] = medias_part[3]/12500;

		return NULL;
}

int main ()
{
	pthread_t thread_id1;
	pthread_t thread_id2;
	pthread_t thread_id3;
	pthread_t thread_id4;
	
	
	float v[50000];
	int i;
	float media = 0;

	//criando vetor

	for(i=0;i<50000;i++){
		srandom(i+1);
		v[i] = (float) random();
	}

	//iniciando threads

	pthread_create(&thread_id1, NULL,&search1,v);
	pthread_create(&thread_id2, NULL,&search2,v);
	pthread_create(&thread_id3, NULL,&search3,v);
	pthread_create(&thread_id4, NULL,&search4,v);

	pthread_join(thread_id4,NULL);
	pthread_join(thread_id3,NULL);
	pthread_join(thread_id2,NULL);
	pthread_join(thread_id1,NULL);

	//comparando resultados das 4 threads

	for (i = 0; i < 4; i++)
	{
		media += medias_part[i];
	}

	media = media/4;

	printf("Media por busca em partes: %.2lf\n", media);


	
	return 0;
}