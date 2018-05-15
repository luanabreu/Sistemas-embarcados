#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <time.h>
#include <sys/types.h>

int fd;
int fp[2];

int fd;

void fechar(){
	close(fd);
	fd = open("/sys/class/gpio/unexport",O_WRONLY);
	write(fd,"20",2);
	write(fd,"21",2);
	close(fd);
	printf("Fechando programa\n");
	sleep(1);
	exit(0);
}


int main(){

<<<<<<< HEAD:Questionários Práticos/Aula_14/ex3.c

	int fp[2];
=======
>>>>>>> 96d48fe6e6533ec480b7f78b45a10a4a31614163:Questionários Práticos/Aula_15/Ex01.c
	pid_t pid_id;

	pipe(fp);

	pid_id = fork();

	signal(SIGINT,fechar);

	if(pid_id == 0){
		//processo filho

		int bf = 1;

		//Setando como export
		printf("Realizando o export 20\n");
		fd = open("/sys/class/gpio/export",O_WRONLY);
		write(fd,"20",2);
		close(fd);

		//Setando como saída
		printf("Iniciando o pin 20 como saída\n");
		fd = open("/sys/class/gpio/gpio20/direction",O_WRONLY);
		write(fd,"out",4);
		close(fd);


		fd = open("/sys/class/gpio/gpio20/value",O_WRONLY);
		printf("Iniciando o blink em 20\n");
		while(1){
			read(fp[0],&bf,sizeof(int));
			printf("F = %d\n",500000/bf);
			write(fd,"1",2);
			usleep(500000/bf);
			write(fd,"0",2);
			usleep(500000/bf);
		}
	}

	else{

		//processo pai
		int bp = 1;
		char btn;
		int bp_pass;

		//Setando como export
		printf("Realizando o export 21\n");
		fd = open("/sys/class/gpio/export",O_WRONLY);
		write(fd,"21",2);
		close(fd);

		//Setando como saída
		printf("Iniciando o pin como saída 21\n");
		fd = open("/sys/class/gpio/gpio21/direction",O_WRONLY);
		write(fd,"in",4);
		close(fd);

		fd = open("/sys/class/gpio/gpio21/value",O_RDWR);
		printf("Pronto para capturar gpio21\n");
		while(1){
			lseek(fd,0,SEEK_SET);
			read(fd,&btn,2);
			printf("Freq = %d BTN = %c\n",bp,btn);
			if(btn == '1'){
				bp = 2*bp;
				if(bp == 128) bp=1;
			}
			bp_pass = bp;
			write(fp[1],&bp_pass,sizeof(bp));
			usleep(500000);
		}

	}

	return 0;
}
