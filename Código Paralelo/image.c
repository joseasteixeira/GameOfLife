#include <stdio.h>
#include "gol.h"

// Salva o estado atual da grade em um arquivo no formato PBM
void save_pbm(Cell **grid, int height, int width, int iter) {
    char imagem[64];
    snprintf(imagem, sizeof(imagem), "gol_%d.pbm", iter);

    FILE *fp = fopen(imagem, "w");
    if (!fp) {
        perror("Erro ao criar arquivo PBM");
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
