#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>


int main()
{
    pid_t pid_filho;
    int fd[2];
    
    pipe(fd);
    pid_filho = fork();

    // Codigo do filho    
    if(pid_filho == 0)
    {
        char nome[50];

        scanf("%s",nome);

        if(write(fd[1],nome,sizeof(nome))<0){
            printf("Erro na escrita\n");
        }
    }
    
    // Codigo do pai
    else
    {
        char nome[50];
        sleep(1);

        if(read(fd[0],nome,50)<0){
            printf("Erro na escrita\n");
        }
        else{
            printf("%s\n",nome);
        }
    }
    return 0;
}
