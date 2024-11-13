#include <unistd.h>
#include <stdio.h>
#include <signal.h>


void handler(int num) {
    printf("Interrompi o sleep!\n");
    
}

int main(int argc, char *argv[]) {
    struct sigaction st;
    st.sa_handler = SIG_IGN;
    st.sa_flags = 0;
    sigemptyset(&st.sa_mask);
    sigaction(SIGTERM, &st, NULL); 
    
    printf("Meu pid: %d\n", getpid());
    printf("Tempo restante: %d\n", sleep(20));

}
