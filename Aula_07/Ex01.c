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
        int buf_filho,i;
        printf("Filho vai ler o pipe\n");
        
        for(i=0;i<10;i++){
            if(read(fd[0], &buf_filho, sizeof(int)) < 0) {
                printf("Erro na leitura do pipe\n");
            }
            else{
                printf("Valor lido pelo filho = %d\n", buf_filho);
            }
            sleep(1); 
        }

        printf("Filho terminando sua execução\n");



    }
    
    // Codigo do pai
    else
    {
        int buf_pai,i;

        for(i=0;i<10;i++){
           buf_pai = i+1;
           if (write(fd[1], &buf_pai, sizeof(buf_pai)) < 0){
                printf("Erro na escrita do pipe\n");
           }
           sleep(1); 
        }
        printf("Pai terminando sua execução\n");
        sleep(1);
    }
    return 0;
}
