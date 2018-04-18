#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

int v_global = 0; // Variavel global para este exemplo

void Incrementa_Variavel_Global(pid_t id_atual);

int main(int argc, char **argv){
    pid_t child_pid_1;
    pid_t child_pid_2;
    pid_t child_pid_3;
    //int v_global = 0;
    
    //printf("numero do processo original: %d\n", (int) getpid()); 

    child_pid_1 = fork();
    
    if(child_pid_1 == 0){
        printf("filho_1 %d e v_global %d", (int) getpid(),v_global); 
        Incrementa_Variavel_Global(getpid());      
    }

    else{
        child_pid_2 = fork();
        if(child_pid_2 == 0){
            printf("filho_2 %d e v_global %d", (int) getpid(),v_global);
            Incrementa_Variavel_Global(getpid());      
        }

        else{
            
            child_pid_3 = fork();
            if(child_pid_3 == 0){
                printf("filho_3 %d e v_global %d", (int) getpid(),v_global);
                Incrementa_Variavel_Global(getpid());      
            }
            else{
                printf("pai %d e v_global %d", (int) getpid(),v_global);  
                //Incrementa_Variavel_Global(getpid());  
            }    
        }
    }

    //printf("v_global = %d\n", v_global);

    
    return 0;
}

void Incrementa_Variavel_Global(pid_t id_atual)
    {
        v_global++;
        printf("ID do processo que executou esta funcao = %d\n", id_atual);
        printf("v_global = %d\n", v_global);
    }

