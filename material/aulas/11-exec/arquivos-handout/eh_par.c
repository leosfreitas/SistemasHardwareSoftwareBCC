#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Erro: o programa deve receber apenas um número como argumento.\n");
        return -1;
    }

    long numero = atol(argv[1]);

    if (numero < 0) {
        return -1;
    } else if (numero % 2 == 0) {
        return 1;
    } else {
        return 0;
    }
}
