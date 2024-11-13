#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

struct soma_parcial_args {
    double *vetor;
    int start, end;
    pthread_mutex_t *mutex;  // Ponteiro para o mutex (ou NULL no cálculo sequencial)
};

double soma = 0;

void *soma_parcial(void *_arg) {
    struct soma_parcial_args *spa = _arg;

    for (int i = spa->start; i < spa->end; i++) {
        if (spa->mutex) pthread_mutex_lock(spa->mutex);  // Trava o mutex apenas se ele existir
        soma += spa->vetor[i];
        if (spa->mutex) pthread_mutex_unlock(spa->mutex);  // Destrava o mutex apenas se ele existir
    }

    return NULL;
}

int main(int argc, char *argv[]) {
    double *vetor = NULL;
    int n;

    // Inicializa o mutex
    pthread_mutex_t mutex_soma = PTHREAD_MUTEX_INITIALIZER;

    // Lê o tamanho do vetor
    printf("Digite o tamanho do vetor: ");
    scanf("%d", &n);

    vetor = malloc(sizeof(double) * n);
    printf("Digite os elementos do vetor:\n");
    for (int i = 0; i < n; i++) {
        scanf("%lf", &vetor[i]);
    }

    /* TODO: criar thread_t e soma_parcial_args aqui */
    pthread_t tids[4];
    struct soma_parcial_args args[4];

    int chunk_size = n / 4;

    // Criação de 4 threads para somar partes do vetor
    for (int i = 0; i < 4; i++) {
        args[i].vetor = vetor;
        args[i].start = i * chunk_size;
        args[i].end = (i == 3) ? n : args[i].start + chunk_size;  // A última thread pega o restante
        args[i].mutex = &mutex_soma;  // Passa o mutex para os argumentos

        if (pthread_create(&tids[i], NULL, soma_parcial, &args[i]) != 0) {
            fprintf(stderr, "Erro ao criar a thread %d\n", i + 1);
            free(vetor);
            return 1;
        }
    }

    /* TODO: esperar pela conclusão */
    for (int i = 0; i < 4; i++) {
        pthread_join(tids[i], NULL);
    }

    printf("Paralela: %lf\n", soma);

    // Soma sequencial para verificar o resultado
    soma = 0;
    struct soma_parcial_args aa;
    aa.vetor = vetor;
    aa.start = 0;
    aa.end = n;
    aa.mutex = NULL;  // Define mutex como NULL para o cálculo sequencial
    soma_parcial(&aa);
    printf("Sequencial: %lf\n", soma);

    // Libera a memória alocada para o vetor e destrói o mutex
    free(vetor);
    pthread_mutex_destroy(&mutex_soma);

    return 0;
}
