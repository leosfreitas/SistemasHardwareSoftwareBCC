#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int numero_filhos;
    pid_t pid;

    printf("Digite o número de processos filhos: ");
    scanf("%d", &numero_filhos);

    for (int i = 0; i < numero_filhos; i++) {
        pid = fork();
        sleep(5);
        if (pid == 0) {
            printf("Eu sou um processo filho, com PID=%d, criado por PID=%d\n", getpid(), getppid());
            return 0;
        }
    }

    for (int i = 0; i < numero_filhos; i++) {
        wait(NULL);    
    }

    return 0;
}