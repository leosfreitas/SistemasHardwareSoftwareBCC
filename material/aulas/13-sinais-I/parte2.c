#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

int main() {
    pid_t filho;

    filho = fork();
    if (filho == 0) {
        // Código do processo filho
        printf("Sou o processo filho e meu pid é: %d\n", getpid());
        while (1) {
            // Loop infinito
        }
    } else {
        // Código do processo pai
        int wstatus;
        pid_t pid_filho_terminado = wait(&wstatus);  // Aguarda o término do filho e captura seu PID
        printf("Pid do filho que terminou = %d\n", pid_filho_terminado);

        // Verifica se o filho terminou devido a um sinal e mostra o número do sinal
        if (WIFSIGNALED(wstatus)) {
            int sinal = WTERMSIG(wstatus);
            printf("O processo filho foi terminado pelo sinal: %d\n", sinal);
        }
    }

    return 0;
}
