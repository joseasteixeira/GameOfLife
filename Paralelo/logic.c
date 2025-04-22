#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include "gol.h"

// Aplica as regras do Jogo da Vida e atualiza a grade para a próxima geração
void gen_next() {
    // Cria uma nova grade temporária
    Cell **new_grid = malloc(HEIGHT * sizeof(Cell *));
    for (int i = 0; i < HEIGHT; i++) {
        new_grid[i] = malloc(WIDTH * sizeof(Cell));
    }

    // Copia o estado atual da grade para a nova
    #pragma omp parallel for
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            new_grid[i][j] = grid[i][j];
        }
    }

    int num_threads = omp_get_max_threads();
    int colunas_por_thread = WIDTH / num_threads;
    int resto = WIDTH % num_threads;

    #pragma omp parallel
    {   
        int tid = omp_get_thread_num();

        // Define a faixa de colunas que cada thread irá processar
        int start_col = tid * colunas_por_thread + (tid < resto ? tid : resto);
        int end_col = start_col + colunas_por_thread + (tid < resto ? 1 : 0);
        if (end_col > WIDTH) end_col = WIDTH;

        // Garantir que as bordas periódicas sejam consideradas.
        int left_col = (start_col - 1 + WIDTH) % WIDTH;
        int right_col = (end_col) % WIDTH;

        // Aplica as regras do jogo
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
                    new_grid[i][j].state = (alive_count < 2 
                        || alive_count > 3) ? DEAD : ALIVE;
                } else {
                    if (alive_count == 3) {
                        new_grid[i][j].state = ALIVE;
                    }
                }
            }
        }

        // Comunicação das bordas
        // Troca de colunas entre as tarefas adjacentes
        if (tid > 0) {
            /* Copiar a última coluna da tarefa anterior para a 
            primeira coluna da tarefa atual. */
            for (int i = 0; i < HEIGHT; i++) {
                new_grid[i][start_col] = grid[i][left_col];
            }
        }
        if (tid < num_threads - 1) {
            /* Copiar a última coluna da tarefa atual para a 
            primeira coluna da próxima tarefa. */
            for (int i = 0; i < HEIGHT; i++) {
                new_grid[i][right_col] = grid[i][end_col];
            }
        }

        // Sincroniza para garantir que a comunicação foi concluída
        #pragma omp barrier

        // Atualiza a grade original com os novos estados
        #pragma omp for collapse(2)
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                grid[i][j] = new_grid[i][j];
            }
        }

    }

    // Libera a memória da grade temporária
    for (int i = 0; i < HEIGHT; i++) {
        free(new_grid[i]);
    }
    free(new_grid);
}
