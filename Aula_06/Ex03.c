#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

//NÃO CONCLUIDO!!!

int main(int argc,char **argv)
{
    char argumentos[100][100];
    pid_t filho = fork();
    int i;

    for(i=1;i<=argc;i++){
        sprintf(argumentos[i],"\"%s\"",argv[i]);
        //printf("%s\n", argumentos[i]);
    }

    if(filho == 0){
        printf("Filho\n");
        execvp(argumentos[2],argumentos);
    }

    else{
        printf("Pai\n");
    }

    return 0;
}