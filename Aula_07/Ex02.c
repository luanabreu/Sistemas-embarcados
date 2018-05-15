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
        
        char buf_filho[100];

        //sleep(1);

        strcpy(buf_filho,"Pai, qual é a verdadeira essência da sabedoria?");

        if (write(fd[1], buf_filho, sizeof(buf_filho)) < 0){
            printf("Erro na escrita do pipe\n");
        }

        sleep(1); 

        if(read(fd[0], buf_filho, 100) < 0) {
            printf("Erro na leitura do pipe\n");
        }
        else{
            printf("Pai = %s\n", buf_filho);
        }

        sleep(1);

        strcpy(buf_filho,"Mas até uma criança de três anos sabe disso!");

        if (write(fd[1], buf_filho, sizeof(buf_filho)) < 0){
            printf("Erro na escrita do pipe\n");
        }

        sleep(1);

        if(read(fd[0], buf_filho, 100) < 0) {
            printf("Erro na leitura do pipe\n");
        }
        else{
            printf("Pai = %s\n", buf_filho);
        }

        sleep(1);

    }
    
    // Codigo do pai
    else
    {
        char buf_pai[100];

        sleep(1);

        if(read(fd[0], buf_pai, 100) < 0) {
            printf("Erro na leitura do pipe\n");
        }
        else{
            printf("Filho = %s\n", buf_pai);
        }

        sleep(1);

        strcpy(buf_pai,"Não façais nada violento, praticai somente aquilo que é justo e equilibrado.");

        if (write(fd[1], buf_pai, sizeof(buf_pai)) < 0){
            printf("Erro na escrita do pipe\n");
        }

        sleep(1); 

        if(read(fd[0], buf_pai, 100) < 0) {
            printf("Erro na leitura do pipe\n");
        }
        else{
            printf("Filho = %s\n", buf_pai);
        }

        sleep(1);

        strcpy(buf_pai,"Sim, mas é uma coisa difícil de ser praticada até mesmo por um velho como eu...");

        if (write(fd[1], buf_pai, sizeof(buf_pai)) < 0){
            printf("Erro na escrita do pipe\n");
        }

        sleep(1);

    }
    return 0;
}
