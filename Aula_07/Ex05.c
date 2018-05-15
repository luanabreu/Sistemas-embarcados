#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void cntrl_c()
{
	printf("Processo Terminado!\n");
	exit(1);
}

void contagem(){
	system("ps");
	alarm(1);
}

int main()
{
	signal(SIGINT,cntrl_c);
	signal(SIGALRM, contagem);
	printf("Pressione CTRL-C para fechar o programa.\n");
	alarm(1);
	while(1);	
	return 0;
}
