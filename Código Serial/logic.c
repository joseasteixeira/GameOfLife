#include <stdlib.h>
#include "gol.h"

void gen_next() {
    int granularidade = 4;

    // Cria uma nova grade temporária
    Cell **new_grid = malloc(HEIGHT * sizeof(Cell *));
    for (int i = 0; i < HEIGHT; i++) {
        new_grid[i] = malloc(WIDTH * sizeof(Cell));
    }

    // Calcula número de colunas por bloco
    int base_block_width = WIDTH / granularidade;
    int remainder = WIDTH % granularidade;

    // Paraleliza por blocos de colunas
    for (int b = 0; b < granularidade; b++) {
        // Define início e fim do bloco considerando o resto
        int start_col = b * base_block_width + (b < remainder ? b : remainder);
        int block_width = base_block_width + (b < remainder ? 1 : 0);
        int end_col = start_col + block_width;

        // Aplica as regras do jogo apenas nas colunas do bloco
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = start_col; j < end_col; j++) {
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
                    new_grid[i][j].state = (alive_count < 2 || alive_count > 3) ? DEAD : ALIVE;
                } else {
                    new_grid[i][j].state = (alive_count == 3) ? ALIVE : DEAD;
                }
            }
        }
    }

    // Sincronização implícita garantida após o for paralelo
    // Copia os novos estados de volta para a grade original
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            grid[i][j] = new_grid[i][j];
        }
    }

    // Libera a memória da grade temporária
    for (int i = 0; i < HEIGHT; i++) {
        free(new_grid[i]);
    }
    free(new_grid);
}
