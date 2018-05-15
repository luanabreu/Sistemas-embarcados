#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

int main (int argc, char* const argv[])
{
	int socket_id;
	struct sockaddr socket_struct;
	int numbers;


	socket_id = socket(PF_LOCAL, SOCK_STREAM,0);
	socket_struct.sa_family = AF_LOCAL;
	strcpy(socket_struct.sa_data,"/tmp/socket1");
	
	connect(socket_id,&socket_struct,sizeof(socket_struct));

	for(numbers=1;numbers<=10;numbers++){
		write(socket_id,&numbers,sizeof(int));
		printf("O cliente está enviando = %d\n",numbers);
		sleep(1);
	}
	
	close(socket_id);

	sleep(1);

	return 0;
}