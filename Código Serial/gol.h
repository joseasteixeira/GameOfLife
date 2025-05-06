#ifndef GAME_H
#define GAME_H

// Enumeração que define os dois possíveis estados de uma célula: morta ou viva
typedef enum {
    DEAD,
    ALIVE
} State;

// Estrutura que representa uma célula com um estado (viva ou morta)
typedef struct {
    State state;
} Cell;

extern Cell **grid;     // Ponteiro para a grade dinâmica de células
extern Cell **grid_aux;     //Poneiro auxiliar
extern int WIDTH;     // Largura da grade
extern int HEIGHT;    // Altura da grade


void allocate_grid();  // Aloca dinamicamente a grade
void free_grid();      // Libera a memória da grade
void init_grid();      // Inicializa a grade com estados aleatórios
void gen_next();       // Aplica as regras do jogo e gera a próxima geração
void save_pbm(Cell **grid, int height, int width, int iter);  // Salva a grade em imagem PBM

#endif

int load_grid_from_file(const char *estado_inicial);

