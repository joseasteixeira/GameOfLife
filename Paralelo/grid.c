#include <stdlib.h>
#include <omp.h>
#include "gol.h"

// Variáveis globais da grade e suas dimensões
Cell **grid = NULL;
int WIDTH = 0;
int HEIGHT = 0;

// Aloca dinamicamente a matriz (grade) de células com base na altura e largura
void allocate_grid() {
    grid = malloc(HEIGHT * sizeof(Cell *));
    #pragma omp parallel for
    for (int i = 0; i < HEIGHT; i++) {
        grid[i] = malloc(WIDTH * sizeof(Cell));
    }
}

// Libera a memória previamente alocada para a grade
void free_grid() {
    for (int i = 0; i < HEIGHT; i++) {
        free(grid[i]);
    }
    free(grid);
}

// Inicializa a grade com valores aleatórios (células vivas ou mortas)
void init_grid() {
    #pragma omp parallel for collapse(2)
    for (size_t i = 0; i < HEIGHT; i++) {
        for (size_t j = 0; j < WIDTH; j++) {

            // Cria uma semente única por iteração com base em posição + thread
            unsigned int seed = (unsigned int)(omp_get_thread_num() + i * WIDTH + j);

            if (rand_r(&seed) % 2 == 0 && rand_r(&seed) % 5 == 0) {                grid[i][j].state = ALIVE;
            } else {
                grid[i][j].state = DEAD;
            }
        }
    }
}
