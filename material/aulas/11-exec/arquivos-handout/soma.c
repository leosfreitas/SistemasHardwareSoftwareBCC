#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Erro: o programa precisa de pelo menos 2 argumentos.\n");
        return 1;
    }

    double soma = 0;

    for (int i = 1; i < argc; i++) { // Começa de 1 para ignorar o nome do programa
        double valor = atof(argv[i]); // Converte o argumento para double
        soma += valor;
    }

    printf("A soma dos argumentos é: %.2f\n", soma);

    return 0;
}
