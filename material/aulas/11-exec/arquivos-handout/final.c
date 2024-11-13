#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int numero;
    char numero_str[20];

    while (1) {
        printf("Digite um número: ");
        scanf("%d", &numero);

        sprintf(numero_str, "%d", numero);  

        pid_t pid = fork();

        if (pid == 0) {
            char *args[] = {"./eh_par", numero_str, NULL};
            execvp(args[0], args);
            perror("Erro ao executar eh_par");
            exit(1);
        } else if (pid > 0) {
            int status;
            wait(&status);

            int retorno = status >> 8; 
            
            if (retorno == 1) {
                printf("É par!\n");
            } else if (retorno == 0) {
                printf("Não é par!\n");
            } else if (retorno == 255 || retorno == -1) { 
                printf("Número negativo. Programa encerrado.\n");
                break;
            }
        } else {
            perror("Erro ao criar processo filho");
            exit(1);
        }
    }

    return 0;
}
