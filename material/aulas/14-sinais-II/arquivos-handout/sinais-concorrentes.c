#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int status = 0;

void operacao_lenta() {
    sleep(10);
}

void sigint_handler(int num) {
    status += 1;
    printf("Chamou Ctrl+C; status=%d\n", status);
    operacao_lenta();
    printf("SIGINT: Vou usar status agora! status=%d\n", status);
}

void sigterm_handler(int num) {
    status += 1;
    printf("Recebi SIGTERM; status=%d\n", status);
    operacao_lenta();
    printf("SIGTERM: Vou usar status agora! status=%d\n", status);
}

int main() {
    struct sigaction handler;

    // Configurações para o manipulador SIGINT
    handler.sa_handler = sigint_handler;
    handler.sa_flags = 0;
    sigemptyset(&handler.sa_mask);
    sigaddset(&handler.sa_mask, SIGTERM);  // Bloqueia SIGTERM enquanto SIGINT é tratado
    sigaction(SIGINT, &handler, NULL);

    // Configurações para o manipulador SIGTERM
    handler.sa_handler = sigterm_handler;
    sigemptyset(&handler.sa_mask);  // Certifique-se de que SIGTERM não bloqueia outros sinais
    sigaddset(&handler.sa_mask, SIGINT);
    sigaction(SIGTERM, &handler, NULL);

    printf("Meu pid: %d\n", getpid());

    while (1) {
        sleep(1);
    }

    return 0;
}
