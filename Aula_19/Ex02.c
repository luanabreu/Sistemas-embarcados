#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <time.h>

//pinos utilizados: 16,20 e 21
//ultimos do lado direito

void open_gpio(){

	int fd;
	int status;

	fd = open("/sys/class/gpio/export",O_WRONLY);

	status = write(fd,"16",2);
//	printf("Abrindo %d\n",status);
	status = write(fd,"20",2);
//	printf("Abrindo %d\n",status);
	status = write(fd,"21",2);
//	printf("Abrindo %d\n",status);

	close(fd);
}

void close_gpio(){

	int fd;
	int status;
	fd = open("/sys/class/gpio/unexport",O_WRONLY);
	status = write(fd,"16",2);
//	printf("Fechando %d\n",status);
	status = write(fd,"20",2);
//	printf("Fechando %d\n",status);
	status = write(fd,"21",2);
//	printf("Fechando %d\n",status);


	close(fd);
	exit(0);
}

void set_direction(int pin, int mode){

	int fd;
	int status;
	char archive[50];

	sprintf(archive,"/sys/class/gpio/gpio%d/direction",pin);
//	printf("Setando direction = %s\n",archive);

	fd = open(archive,O_WRONLY);

	// 0 para out
	if(mode == 0){
		status = write(fd,"out",3);
//		printf("Set Direction %d\n",status);
	}
	// 1 para in
	else{
		status = write(fd,"in",2);
//		printf("Set Direction %d\n",status);
	}

	close(fd);
}

void set_value(int pin, int value){

	int fd;
	char archive[50];
	int status;

	sprintf(archive,"/sys/class/gpio/gpio%d/value",pin);
//	printf("Setando value = %s\n",archive);

	fd = open(archive,O_WRONLY);

	// 0 para baixo
	if(value == 0){
		status = write(fd,"0",1);
//		printf("Set Value %d\n",status);
	}
	// 1 para alto
	else{
		status = write(fd,"1",1);
//		printf("Set Value %d\n",status);
	}

	close(fd);

}

void meuamigocharlie(int led){

	switch (led){
		case 1:
			set_direction(16,0);
			set_direction(20,0);
			set_direction(21,1);

			set_value(16,1);
			set_value(20,0);

			break;

		case 2:
			set_direction(16,0);
			set_direction(20,0);
			set_direction(21,1);

			set_value(16,0);
			set_value(20,1);

			break;

		case 3:
			set_direction(16,0);
			set_direction(20,1);
			set_direction(21,0);

			set_value(16,1);
			set_value(21,0);

			break;

		case 4:
			set_direction(16,0);
			set_direction(20,1);
			set_direction(21,0);

			set_value(16,0);
			set_value(21,1);

			break;

		case 5:
			set_direction(16,1);
			set_direction(20,0);
			set_direction(21,0);

			set_value(20,1);
			set_value(21,0);

			break;

		case 6:

			set_direction(16,1);
			set_direction(20,0);
			set_direction(21,0);

			set_value(20,0);
			set_value(21,1);

			break;
		}
}

int main(){

	//setando gpio
	int n;

	signal(SIGINT,close_gpio);

	open_gpio();

	while(1){

		n=0;
		while(n!=100){
			meuamigocharlie(1);
			usleep(10000/2);
			meuamigocharlie(2);
			if(usleep(10000/2)==0) n++;
		}

		n=0;
		while(n!=100){

			meuamigocharlie(3);
			usleep(10000/2);
			meuamigocharlie(4);
			if(usleep(10000/2)==0) n++;
		}

		n=0;
		while(n!=100){

			meuamigocharlie(5);
			usleep(10000/2);
			meuamigocharlie(6);
			if(usleep(10000/2)==0) n++;
		}
	}

	close_gpio();

	return 0;
}

