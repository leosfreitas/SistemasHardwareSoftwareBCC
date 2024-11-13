#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>  

int main() {
    pid_t filho;

    filho = fork();
    if (filho == 0) {
        printf("Sou o processo filho e meu pid é: %d\n", getpid());
        int i = 1 / 0;  
        printf("Divisão por zero!\n");
    } else {
        int wstatus;
        wait(&wstatus);
        
        printf("Pid do filho que terminou = %d\n", filho);

        printf("WIFEXITED: %d\n", WIFEXITED(wstatus));
        printf("WIFSIGNALED: %d\n", WIFSIGNALED(wstatus));
        
        if (WIFSIGNALED(wstatus)) {
            int signal_num = WTERMSIG(wstatus);
            printf("O processo filho foi terminado pelo sinal: %s\n", strsignal(signal_num));
        }
    }

    return 0;
}
