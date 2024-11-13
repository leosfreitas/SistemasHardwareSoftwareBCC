#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int numero1, numero2;
    pid_t filho1, filho2, filho3, filho4;

    printf("Digite o primeiro número inteiro: ");
    scanf("%d", &numero1);

    printf("Digite o segundo número inteiro: ");
    scanf("%d", &numero2);

    filho1 = fork();

    if (filho1 == 0) {
        int result = numero1 - numero2;
        printf("O resultado é: %d\n", result);
        exit(0);
    } else {
        filho2 = fork();
        if (filho2 == 0) {
            int result = numero1 + numero2;
            printf("O resultado é: %d\n", result);
            exit(0);
        } else {
            filho3 = fork();
            if (filho3 == 0) {
                int result = numero1 / numero2;
                printf("O resultado é: %d\n", result);
                exit(0);
            } else {
                filho4 = fork();
                if (filho4 == 0) {
                    int result = numero1 * numero2;
                    printf("O resultado é: %d\n", result);
                    exit(0);
                } else {
                    wait(NULL);
                    wait(NULL);
                    wait(NULL);
                    wait(NULL);
                    printf("Os processos filhos acabaram.\n");
                }
            }
        }
    }
    return 0;
}

// código com for: 

// #include <sys/types.h>
// #include <sys/wait.h>
// #include <unistd.h>
// #include <stdio.h>
// #include <stdlib.h>

// int main() {
//     int numero1, numero2;

//     printf("Digite o primeiro número inteiro: ");
//     scanf("%d", &numero1);

//     printf("Digite o segundo número inteiro: ");
//     scanf("%d", &numero2);

//     for (int i = 0; i < 4; i++) {
//         pid_t filho = fork();

//         if (filho == 0) {
//             int result;
//             switch (i) {
//                 case 0:
//                     result = numero1 - numero2;
//                     printf("O resultado da subtração é: %d\n", result);
//                     break;
//                 case 1:
//                     result = numero1 + numero2;
//                     printf("O resultado da adição é: %d\n", result);
//                     break;
//                 case 2:
//                     if (numero2 != 0) {
//                         result = numero1 / numero2;
//                         printf("O resultado da divisão é: %d\n", result);
//                     } else {
//                         printf("Divisão por zero não permitida.\n");
//                     }
//                     break;
//                 case 3:
//                     result = numero1 * numero2;
//                     printf("O resultado da multiplicação é: %d\n", result);
//                     break;
//             }
//             exit(0);
//         }
//     }

//     for (int i = 0; i < 4; i++) {
//         wait(NULL);
//     }
//     printf("Os processos filhos acabaram.\n");

//     return 0;
// }
