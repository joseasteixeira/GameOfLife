#include <stdlib.h>
#include <stdio.h>
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

//define o estado inicial a partir de um arquivo de texto
int load_grid_from_file(const char *estado_inicial) {
    FILE *fp = fopen(estado_inicial, "r");
    if (!fp) {
        perror("Erro ao abrir arquivo de estado inicial");
        return 0;
    }
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            int value;
            if (fscanf(fp, "%1d", &value) != 1) {
                printf("Erro ao ler valor da célula em [%d][%d]\n", i, j);
                fclose(fp);
                return 0;
            }
            grid[i][j].state = (value == 1) ? ALIVE : DEAD;
        }
    }

    fclose(fp);
    return 1;
}