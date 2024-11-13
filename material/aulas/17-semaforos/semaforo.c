#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int thread_count = 0; // Conta as threads que chegaram ao ponto de encontro

void *thread_function(void *arg) {
    int thread_id = *((int *)arg);
    
    printf("Thread %d: Antes do ponto de encontro\n", thread_id);
    
    // Começo do Rendezvous
    pthread_mutex_lock(&mutex);
    thread_count++;
    
    // Se as duas threads chegaram, libera ambas
    if (thread_count == 2) {
        pthread_cond_broadcast(&cond);
    } else {
        // Espera a outra thread chegar
        while (thread_count < 2) {
            pthread_cond_wait(&cond, &mutex);
        }
    }
    
    pthread_mutex_unlock(&mutex);
    // Fim do Rendezvous
    
    printf("Thread %d: Depois do ponto de encontro\n", thread_id);
    
    return NULL;
}

int main() {
    pthread_t t1, t2;
    int id1 = 1, id2 = 2;
    
    // Criação das threads
    pthread_create(&t1, NULL, thread_function, &id1);
    pthread_create(&t2, NULL, thread_function, &id2);
    
    // Espera as threads terminarem
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    
    return 0;
}
