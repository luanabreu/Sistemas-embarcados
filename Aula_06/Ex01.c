#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

int main(int argc, char **argv){
    pid_t child_pid_1;
    pid_t child_pid_2;
    pid_t child_pid_3;
    
    printf("numero do processo original: %d\n", (int) getpid()); 

    child_pid_1 = fork();
    
    if(child_pid_1 == 0){
        printf("filho_1 %d\n", (int) getpid()); 
      
    }

    else{
        child_pid_2 = fork();
        if(child_pid_2 == 0){
            printf("filho_2 %d\n", (int) getpid());      
        }

        else{
            
            child_pid_3 = fork();
            if(child_pid_3 == 0){
                printf("filho_3 %d\n", (int) getpid());      
            }
            else{
                printf("pai %d\n", (int) getpid());    
            }    
        }
    }

    
    return 0;
}
