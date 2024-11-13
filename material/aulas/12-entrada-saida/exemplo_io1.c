/* POSIX headers */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/* Standard C */
#include <stdio.h>

int main (int argc, char *argv[]) {
    char arq1[100]; // nomes do arquivo, recebido via scanf
    char buf[1]; // local usado para guardar os dados lidos de arq1
    
    scanf("%s", arq1);
    int fd1 = open(arq1, O_RDONLY);
    for (int i = 0; i < 5; i++) {
        read(fd1, buf, 1);
        printf("Caracter lido: %c\n", buf[0]);
    }
    close(fd1);
    
    return 0;
}

// int main(int argc, char *argv[]) {
//     char arq1[100]; // Nome do arquivo, recebido via scanf
//     char buf[1];    // Local usado para guardar os dados lidos de arq1

//     // Lê o nome do arquivo a partir do usuário
//     scanf("%s", arq1);

//     // Abre o arquivo para leitura
//     int fd1 = open(arq1, O_RDONLY);
//     if (fd1 == -1) {
//         perror("Erro ao abrir o arquivo");
//         return 1;
//     }

//     // Lê o arquivo caractere por caractere até o final
//     while (read(fd1, buf, 1) > 0) {
//         printf("Caracter lido: %c\n", buf[0]);
//     }

//     // Fecha o arquivo
//     close(fd1);
    
//     return 0;
// }