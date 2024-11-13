#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Uso: %s <arquivo_origem> <arquivo_destino>\n", argv[0]);
        return 1;
    }

    // Abrindo o arquivo de origem para leitura
    int fd_origem = open(argv[1], O_RDONLY);
    if (fd_origem == -1) {
        perror("Erro ao abrir o arquivo de origem");
        return 1;
    }

    // Abrindo o arquivo de destino para escrita (cria ou substitui)
    int fd_destino = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_destino == -1) {
        perror("Erro ao abrir o arquivo de destino");
        close(fd_origem);
        return 1;
    }

    // Buffer para armazenar 100 caracteres por vez
    char buffer[100];
    int bytes_lidos;

    // Lendo e escrevendo em blocos de 100 bytes
    while ((bytes_lidos = read(fd_origem, buffer, sizeof(buffer))) > 0) {
        if (write(fd_destino, buffer, bytes_lidos) != bytes_lidos) {
            perror("Erro ao escrever no arquivo de destino");
            close(fd_origem);
            close(fd_destino);
            return 1;
        }
    }

    if (bytes_lidos == -1) {
        perror("Erro ao ler o arquivo de origem");
    }

    // Fechando os descritores de arquivo
    close(fd_origem);
    close(fd_destino);

    printf("Cópia concluída com sucesso.\n");
    return 0;
}
