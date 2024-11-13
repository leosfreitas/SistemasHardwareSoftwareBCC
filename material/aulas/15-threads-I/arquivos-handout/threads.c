#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// Estrutura que contém dois inteiros
typedef struct {
    int valor1;
    int valor2;
} Argumentos;

// Função que multiplica os dois valores e retorna o resultado
void *tarefa_print_i(void *arg) {
    Argumentos *args = (Argumentos *) arg;  // Converte o argumento para a estrutura Argumentos
    int *resultado = malloc(sizeof(int));   // Aloca espaço para o resultado
    *resultado = args->valor1 * args->valor2;  // Calcula a multiplicação
    pthread_exit(resultado);  // Retorna o resultado
}

int main() {
    pthread_t *tids = malloc(sizeof(pthread_t) * 4);         // Aloca vetor de pthread_ts
    Argumentos *vi = malloc(sizeof(Argumentos) * 4);         // Aloca vetor de 4 estruturas Argumentos

    if (tids == NULL || vi == NULL) {
        fprintf(stderr, "Erro ao alocar memória.\n");
        return 1;
    }

    // Criação das threads em um loop, passando dois valores para cada thread
    for (int i = 0; i < 4; i++) {
        vi[i].valor1 = i + 1;        // Define o primeiro valor da estrutura
        vi[i].valor2 = (i + 1) * 10; // Define o segundo valor da estrutura
        int error = pthread_create(&tids[i], NULL, tarefa_print_i, &vi[i]);
        if (error) {
            fprintf(stderr, "Erro ao criar thread %d\n", i + 1);
            free(tids);
            free(vi);
            return 1;
        }
    }

    printf("Hello from main\n");

    // Espera o término das threads e imprime o resultado da multiplicação
    for (int i = 0; i < 4; i++) {
        int *resultado;
        pthread_join(tids[i], (void **)&resultado);
        printf("Resultado da multiplicação na thread %d: %d\n", i + 1, *resultado);
        free(resultado);  // Libera a memória alocada para o resultado
    }

    // Libera memória alocada
    free(tids);
    free(vi);

    return 0;
}
