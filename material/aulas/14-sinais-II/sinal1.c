#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <signal.h>

int contador = 0;

void sigint_handler(int num)
{
    contador++;
    printf("Chamou Ctrl+C\n");
    if (contador == 3)
    {
        struct sigaction handler;

        handler.sa_handler = SIG_DFL;
        handler.sa_flags = 0;
        sigemptyset(&handler.sa_mask);

        sigaction(SIGINT, &handler, NULL);

        /*
        Envia o sinal para si mesmo.
        Outra forma: raise(SIGINT);
        */
        kill(getpid(), SIGINT);
    }
}

void sigtstp_handler(int num) {
    printf("Recebi SIGTSTP, parando execução...\n");

    // Retorna o comportamento padrão para SIGTSTP
    struct sigaction handler;
    handler.sa_handler = SIG_DFL;
    handler.sa_flags = 0;
    sigemptyset(&handler.sa_mask);

    sigaction(SIGTSTP, &handler, NULL);

    // Envia o sinal SIGTSTP para si mesmo
    raise(SIGTSTP);
}

void sigcont_handler(int num) {
    printf("Continuando!\n");
}


int main() {
    struct sigaction handler;

    // Configuração do handler para SIGINT
    handler.sa_handler = sigint_handler;
    handler.sa_flags = 0;
    sigemptyset(&handler.sa_mask);
    sigaction(SIGINT, &handler, NULL);

    // Configuração do handler para SIGTSTP
    handler.sa_handler = sigtstp_handler;
    handler.sa_flags = 0;
    sigemptyset(&handler.sa_mask);
    sigaction(SIGTSTP, &handler, NULL);

    // Configuração do handler para SIGCONT
    handler.sa_handler = sigcont_handler;
    handler.sa_flags = 0;
    sigemptyset(&handler.sa_mask);
    sigaction(SIGCONT, &handler, NULL);

    printf("Meu pid: %d\n", getpid());

    while (1) {
        sleep(1);
    }

    return 0;
}