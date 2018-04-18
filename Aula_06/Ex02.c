#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

int main(int argc, char **argv){

    char *argumentos;
    int i;

    for(i=1;i<=argc;i++){  

    argumentos = argv[i];

    //printf("%s\n",argumentos);

    system(argumentos);
    }
    
    return 0;
}
