#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>


int main()
{
    pid_t pid_filho_1;
    pid_t pid_filho_2;
    int fd[2];
    
    pipe(fd);
    
    pid_filho_1 = fork();

    // Codigo do filho 1  
    if(pid_filho_1 == 0)
    {
        
        char buf_filho[100];

        strcpy(buf_filho,"Quando o vento passa, é a bandeira que se move.");

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
    
    else
    {
        pid_filho_2 = fork();

        // Codigo do filho 2

        if(pid_filho_2 == 0){

            char buf_filho[100];

            if(read(fd[0], buf_filho, 100) < 0) {
                printf("Erro na leitura do pipe\n");
            }
            else{
                printf("Filho1 = %s\n", buf_filho);
            }

            sleep(1);

            strcpy(buf_filho,"Não, é o vento que se move.");

            if (write(fd[1], buf_filho, sizeof(buf_filho)) < 0){
                printf("Erro na escrita do pipe\n");
            }

            sleep(1);

        }

        // Codigo do pai

        else{

            char buf_pai[100];

            sleep(1);

            if(read(fd[0], buf_pai, 100) < 0) {
                printf("Erro na leitura do pipe\n");
            }
            else{
                printf("Filho2 = %s\n", buf_pai);
            }

            sleep(1);

            strcpy(buf_pai,"Os dois se enganam. É a mente dos senhores que se move.");

            if (write(fd[1], buf_pai, sizeof(buf_pai)) < 0){
                printf("Erro na escrita do pipe\n");
            }

            sleep(1);
        }
        
    }
    return 0;
}
