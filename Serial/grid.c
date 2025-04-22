#include <stdlib.h>
#include "gol.h"

// Variáveis globais da grade e suas dimensões
Cell **grid = NULL;
int WIDTH = 0;
int HEIGHT = 0;

// Aloca dinamicamente a matriz (grade) de células com base na altura e largura
void allocate_grid() {
    grid = malloc(HEIGHT * sizeof(Cell *));
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
    for (size_t i = 0; i < HEIGHT; i++) {
        for (size_t j = 0; j < WIDTH; j++) {
            if (rand() % 2 == 0 && rand() % 5 == 0) {
                grid[i][j].state = ALIVE;
            } else {
                grid[i][j].state = DEAD;
            }
        }
    }
}
