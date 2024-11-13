#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    pid_t pid; 

    printf("Eu sou o processo P1, PID=%d\n", getpid());

    pid = fork();

    if (pid == 0) {
        printf("Eu sou o processo P2, PID=%d, criado por PID=%d\n", getpid(), getppid());
        exit(0);
    } else {
        wait(NULL);
        pid = fork();

        if (pid == 0) {
            printf("Eu sou o processo P3, PID=%d, criado por PID=%d\n", getpid(), getppid());

            pid = fork();

            if (pid == 0) {
                printf("Eu sou o processo P4, PID=%d, criado por PID=%d\n", getpid(), getppid());
                exit(0);
            } else {
                wait(NULL);
                pid = fork();
                if (pid == 0) {
                    printf("Eu sou o processo P5, PID=%d, criado por PID=%d\n", getpid(), getppid());
                    exit(0);
                } else {
                    wait(NULL);
                }
            }
        exit(0);
        } else {
            wait(NULL);
        }
    }

    printf("todos os processos concluiram");
    return 0;


}