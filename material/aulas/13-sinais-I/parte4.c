#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>  // Para strsignal

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

        // Verifica se o processo filho ainda está em execução usando waitpid com WNOHANG
        int wstatus;
        pid_t status_filho = waitpid(filho, &wstatus, WNOHANG);

        if (status_filho == 0) {
            // O processo filho ainda está em execução, então enviamos o sinal SIGKILL
            printf("Pai: enviando SIGKILL para o processo filho (PID=%d)\n", filho);
            kill(filho, SIGKILL);

            // Aguarda o término do processo filho
            pid_t pid_filho_terminado = waitpid(filho, &wstatus, 0);
            printf("Pid do filho que terminou = %d\n", pid_filho_terminado);

            // Verifica se o filho foi finalizado por um sinal e mostra o número e nome do sinal
            if (WIFSIGNALED(wstatus)) {
                int sinal = WTERMSIG(wstatus);
                printf("O processo filho foi terminado pelo sinal: %d (%s)\n", sinal, strsignal(sinal));
            }
        } else if (status_filho == filho) {
            // O processo filho já terminou
            printf("O processo filho (PID=%d) já terminou antes do envio do sinal.\n", filho);
        } else {
            perror("Erro ao verificar o estado do processo filho");
        }
    }

    return 0;
}
