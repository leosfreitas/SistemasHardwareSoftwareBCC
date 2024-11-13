#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>

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
        sleep(10);  // Espera por 10 segundos

        // Envia um sinal SIGKILL para o processo filho
        printf("Pai: enviando SIGKILL para o processo filho (PID=%d)\n", filho);
        kill(filho, SIGKILL);

        // Aguarda o término do processo filho
        int wstatus;
        pid_t pid_filho_terminado = wait(&wstatus);
        printf("Pid do filho que terminou = %d\n", pid_filho_terminado);

        // Verifica se o filho foi finalizado por um sinal e mostra o número e nome do sinal
        if (WIFSIGNALED(wstatus)) {
            int sinal = WTERMSIG(wstatus);
            printf("O processo filho foi terminado pelo sinal: %d (%s)\n", sinal, strsignal(sinal));
        }
    }

    return 0;
}
