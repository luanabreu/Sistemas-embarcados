#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int fd;

void fechar(){
	close(fd);
	fd = open("/sys/class/gpio/unexport",O_WRONLY);
	write(fd,"21",2);
	printf("Fechando programa\n");
	close(fd);
	sleep(1);
	exit(0);
}




int main(){

	float frequencia;
	float periodo;

	signal(SIGINT,fechar);

	printf("Qual a frequência (em Hz)?\n");
	scanf("%f",&frequencia);
	periodo = 1000000/(2*(frequencia));


	//Setando como export
	printf("Realizando o export\n");
	fd = open("/sys/class/gpio/export",O_WRONLY);
	write(fd,"21",2);
	close(fd);
	sleep(1);

	//Setando como saída
	printf("Iniciando o pin como saída\n");
	fd = open("/sys/class/gpio/gpio21/direction",O_WRONLY);
	write(fd,"out",4);
	close(fd);
	sleep(1);



	fd = open("/sys/class/gpio/gpio21/value",O_WRONLY);
	printf("Iniciando o blink com a frequência de %.2f Hz\n",frequencia);
	while(1){
		write(fd,"1",2);
		usleep(periodo);
		write(fd,"0",2);
		usleep(periodo);
	}

	return 0;
}
