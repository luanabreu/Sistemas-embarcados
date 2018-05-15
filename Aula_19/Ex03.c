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

	status = write(fd,"22",2);
	status = write(fd,"23",2);
	status = write(fd,"24",2);
	status = write(fd,"25",2);
	status = write(fd,"27",2);
	status = write(fd,"28",2);
	status = write(fd,"29",2);
	status = write(fd,"5",1);
	status = write(fd,"4",1);

	close(fd);
}

void close_gpio(){

	int fd;
	int status;
	fd = open("/sys/class/gpio/unexport",O_WRONLY);

	status = write(fd,"22",2);
	status = write(fd,"23",2);
	status = write(fd,"24",2);
	status = write(fd,"25",2);
	status = write(fd,"27",2);
	status = write(fd,"28",2);
	status = write(fd,"29",2);
	status = write(fd,"5",1);
	status = write(fd,"4",1);

	close(fd);
	exit(0);
}

void set_direction(int pin, int mode){

	int fd;
	int status;
	char archive[50];

	sprintf(archive,"/sys/class/gpio/gpio%d/direction",pin);

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

void f_7seg(char c){

	switch (c){
		case 1:
			set_direction(4,1);
			set_direction(22,0);
			set_direction(23,0);
			set_direction(24,0);
			set_direction(25,1);
			set_direction(27,0);
			set_direction(28,0);
			set_direction(29,1);


			set_value(4,0);
			set_value(22,0);
			set_value(23,0);
			set_value(24,0);
			set_value(25,1);
			set_value(27,0);
			set_value(28,0);
			set_value(29,1);

			break;

		case 2:
			set_direction(4,1);
			set_direction(22,1);
			set_direction(23,0);
			set_direction(24,1);
			set_direction(25,1);
			set_direction(27,1);
			set_direction(28,1);
			set_direction(29,0);


			set_value(4,0);
			set_value(22,1);
			set_value(23,0);
			set_value(24,1);
			set_value(25,1);
			set_value(27,1);
			set_value(28,1);
			set_value(29,0);

			break;

		default:

			set_direction(4,1);
			set_direction(5,0);
			set_direction(22,0);
			set_direction(23,1);
			set_direction(24,1);
			set_direction(25,1);
			set_direction(27,1);
			set_direction(28,1);
			set_direction(29,1);


			set_value(4,0);
			set_value(23,1);
			set_value(24,1);
			set_value(25,1);
			set_value(27,1);
			set_value(28,1);
			set_value(29,1);

			break;

		}
}

int main(){

	//setando gpio
	int n;

	signal(SIGINT,close_gpio);

	open_gpio();

	//while(1){

		f_7seg('1');
		sleep(2);
		f_7seg('2');
		sleep(2);
		f_7seg('0');
		sleep(2);

	//}

	close_gpio();

	return 0;
}

