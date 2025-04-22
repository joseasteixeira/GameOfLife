#include <stdlib.h>
#include "gol.h"

// Aplica as regras do Jogo da Vida e atualiza a grade para a próxima geração
void gen_next() {
    // Cria uma nova grade temporária
    Cell **new_grid = malloc(HEIGHT * sizeof(Cell *));
    for (int i = 0; i < HEIGHT; i++) {
        new_grid[i] = malloc(WIDTH * sizeof(Cell));
    }

    // Copia o estado atual da grade para a nova
    for (size_t i = 0; i < HEIGHT; i++) {
        for (size_t j = 0; j < WIDTH; j++) {
            new_grid[i][j] = grid[i][j];
        }
    }

    // Aplica as regras do jogo para cada célula
    for (size_t i = 0; i < HEIGHT; i++) {
        for (size_t j = 0; j < WIDTH; j++) {
            int alive_count = 0;
            for (int k = -1; k <= 1; k++) {
                for (int l = -1; l <= 1; l++) {
                    if (k == 0 && l == 0) continue;
                    int row = (i + k + HEIGHT) % HEIGHT;
                    int col = (j + l + WIDTH) % WIDTH;
                    if (grid[row][col].state == ALIVE) {
                        alive_count++;
                    }
                }
            }
            // Aplica as regras de transição
            if (grid[i][j].state == ALIVE) {
                new_grid[i][j].state = (alive_count < 2 
                    || alive_count > 3) ? DEAD : ALIVE;
            } else {
                if (alive_count == 3) {
                    new_grid[i][j].state = ALIVE;
                }
            }
        }
    }

    // Copia os novos estados de volta para a grade original
    for (size_t i = 0; i < HEIGHT; i++) {
        for (size_t j = 0; j < WIDTH; j++) {
            grid[i][j] = new_grid[i][j];
        }
    }

    // Libera a memória da grade temporária
    for (int i = 0; i < HEIGHT; i++) {
        free(new_grid[i]);
    }
    free(new_grid);
}
