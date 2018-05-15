#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <time.h>
#include <sys/types.h>
#include <sys/poll.h>

int fd;

void fechar(){
	close(fd);
	fd = open("/sys/class/gpio/unexport",O_WRONLY);
	write(fd,"21",2);
	close(fd);
	printf("Fechando programa\n");
	sleep(1);
	exit(0);
}


int main(){

	struct pollfd pfd;
	char buffer;
	int btn = 1;

	signal(SIGINT,fechar);

	//export pino 21
	fd = open("/sys/class/gpio/export",O_WRONLY);
	write(fd,"21",2);
	close(fd);
	puts("Definindo export...");

	//edge pino 21
	fd = open("/sys/class/gpio/gpio21/edge",O_WRONLY);
	write(fd,"falling",7);
	close(fd);
	puts("Definindo edge...");

	//direction pino 21
	fd = open("/sys/class/gpio/gpio21/direction",O_WRONLY);
	write(fd,"in",2);
	close(fd);
	puts("Definindo direction...");

	//abrindo valor do pino 21
	pfd.fd = open("/sys/class/gpio/gpio21/value",O_RDONLY);
	if(pfd.fd < 0){printf("Error"); exit(1);}
	puts("Definindo value...");

	//eventos revents do pino 21
	pfd.events = POLLPRI | POLLERR;
	pfd.revents = 0;

	//programa
	printf("Aumentando a frequencia por borta de descida...\n");
	while(1)
	{
		printf("Frequência = %d\n",btn);
		lseek(pfd.fd, 0, SEEK_SET);
		read(pfd.fd, &buffer, 1);
		poll(&pfd, 1, -1);
		btn = 2*btn;
		if(btn == 128) btn=1;
		usleep(100000);
	}


	return 0;
}
