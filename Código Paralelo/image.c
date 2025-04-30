#include <stdio.h>
#include "gol.h"

// Salva o estado atual da grade em um arquivo no formato PBM (imagem preto e branco)
void save_pbm(Cell **grid, int height, int width, int iter) {
    char filename[64];
    snprintf(filename, sizeof(filename), "gol_%d.pbm", iter);  // Gera nome do arquivo

    FILE *fp = fopen(filename, "w");
    if (!fp) {
        perror("Erro ao criar arquivo PBM");  // Mensagem de erro se não conseguir criar
        return;
    }

    // Escreve o cabeçalho do arquivo PBM
    fprintf(fp, "P1\n%d %d\n", width, height);

    // Escreve os dados da grade: 1 para vivo, 0 para morto
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            fprintf(fp, "%d ", grid[i][j].state == ALIVE ? 1 : 0);
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
}
