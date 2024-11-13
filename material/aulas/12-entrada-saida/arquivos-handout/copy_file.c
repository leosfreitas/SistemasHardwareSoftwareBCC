#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Uso: %s <arquivo_origem> <arquivo_destino>\n", argv[0]);
        return 1;
    }

    // Abrindo o arquivo de origem para leitura
    int fd_origem = open(argv[1], O_RDONLY);
    if (fd_origem == -1) {
        if (errno == EACCES) {
            fprintf(stderr, "Erro: Permissão negada ao abrir o arquivo de origem.\n");
        } else {
            perror("Erro ao abrir o arquivo de origem");
        }
        return 1;
    }

    // Abrindo o arquivo de destino para escrita (cria ou substitui)
    // O_APPEND ADICIONA OS CARACTERES DO ARQUIVO DE ORIGEM
    // O_TRUNC SUBSTITUI TUDO
    int fd_destino = open(argv[2], O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd_destino == -1) {
        perror("Erro ao abrir o arquivo de destino");
        close(fd_origem);
        return 1;
    }

    char ch;
    while (1) {
        // Lendo um caractere do arquivo de origem
        int bytes_lidos = read(fd_origem, &ch, 1);
        if (bytes_lidos == -1) {
            perror("Erro ao ler o arquivo de origem");
            close(fd_origem);
            close(fd_destino);
            return 1;
        }
        
        // Verifica se chegou ao fim do arquivo
        if (bytes_lidos == 0) {
            break;
        }

        // Escrevendo o caractere no arquivo de destino
        int bytes_escritos = write(fd_destino, &ch, 1);
        if (bytes_escritos == -1) {
            perror("Erro ao escrever no arquivo de destino");
            close(fd_origem);
            close(fd_destino);
            return 1;
        }
    }

    // Fechando os descritores de arquivo
    close(fd_origem);
    close(fd_destino);

    printf("Cópia concluída com sucesso.\n");
    return 0;
}
