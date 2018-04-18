#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv){

	int fp;
	int cStatus;
	int wStatus;
	char hello[20] = "Ola Mundo\n";

	fp = open("/home/arthur/exercicios/ola_mundo.txt",O_RDWR|O_CREAT,400);

	wStatus = write(fp,&hello,sizeof(hello)-1);
	
	cStatus = close(fp);
	
	return 0;
}