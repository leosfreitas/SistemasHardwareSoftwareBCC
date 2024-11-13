#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid;
    int i;

    printf("Eu sou o processo pai, pid=%d, meu id do programa é 0\n", getpid());

    for (i = 1; i <= 8; i++) {
        pid = fork(); 
        if (pid == 0) {
            printf("Eu sou um processo filho, pid=%d, ppid=%d, meu id do programa é %d\n", getpid(), getppid(), i);
            return 0; 
        }
    }

    return 0;
}
