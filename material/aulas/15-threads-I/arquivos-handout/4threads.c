
#include <pthread.h>
#include <stdio.h>

void *thread1(void *arg) {
    printf("Hello thread 1!\n");
    return NULL;
}

void *thread2(void *arg) {
    printf("Hello thread 2!\n");
    return NULL;
}

void *thread3(void *arg) {
    printf("Hello thread 3!\n");
    return NULL;
}

void *thread4(void *arg) {
    printf("Hello thread 4!\n");
    return NULL;
}

int main() {
    pthread_t tid1, tid2, tid3, tid4;
    
    int error1 = pthread_create(&tid1, NULL, thread1, NULL);
    int error2 = pthread_create(&tid2, NULL, thread2, NULL);
    int error3 = pthread_create(&tid3, NULL, thread3, NULL);
    int error4 = pthread_create(&tid4, NULL, thread4, NULL);


    printf("Hello main\n");
    
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);
    pthread_join(tid4, NULL);
    
    return 0;
}
