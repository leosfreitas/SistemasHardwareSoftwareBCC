#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h> 

int main() {
    int rodando = 1;
    pid_t filho;

    filho = fork();

    if (filho == 0) {
        printf("Acabei filho\n");
        rodando = 0;
    } else {
        while (rodando) {
            printf("Esperando o filho acabar!\n");
            sleep(1);

        }

        wait(NULL);
        printf("O processo filho terminou! O pai também vai terminar agora.\n");
    }
    return 0;
}
