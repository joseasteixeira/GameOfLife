#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "gol.h"

int max_iter = 0;
int intervalo = 0;

int generation=0;

// Lê os parâmetros do arquivo de configuração (.txt)
int ler_configuracoes(const char *arquivo) {
    FILE *config = fopen(arquivo, "r");
    if (!config) {
        perror("Erro ao abrir arquivo de configuração");
        return 0;
    }

    // Ler os valores.
    if (fscanf(config, "%d %d %d %d", &WIDTH, &HEIGHT, &max_iter, &intervalo) != 4) {
        printf("Erro: O arquivo deve conter quatro números inteiros: WIDTH HEIGHT ITERACOES INTERVALO\n");
        fclose(config);
        return 0;
    }

    fclose(config);

    // Verifica se os valores são validos.
    if (WIDTH <= 0 || HEIGHT <= 0 || max_iter <= 0 || intervalo <= 0) {
        printf("Erro: Todos os parâmetros devem ser positivos.\n");
        return 0;
    }

    return 1;
}

// Executa o loop principal do Jogo da Vida
void executar_simulacao(double *tempo_computacao) {
    clock_t start_total = clock();
    clock_t tempo_save_total = 0;

    for (int i = 0; i < max_iter; i++) {
        if ((i + 1) % intervalo == 0) {
            clock_t start_save = clock();
            save_pbm(grid, HEIGHT, WIDTH, i + 1); 
            clock_t end_save = clock();

            tempo_save_total += (end_save - start_save);
        }

        gen_next();
        generation++;
    }

    clock_t end_total = clock();

    // Tempo total - tempo gasto salvando imagens
    *tempo_computacao = (double)(end_total - start_total - tempo_save_total) / CLOCKS_PER_SEC;
}



// Salva um arquivo de texto com o tempo de execução em segundos.
void salvar_tempo_em_arquivo(double tempo_computacao) {
    FILE *fp = fopen("tempos_serial.txt", "a");
    if (fp) {
        fprintf(fp, "%.4f\n", tempo_computacao);
        fclose(fp);
    } else {
        perror("Erro ao abrir arquivo de tempos");
    }
}


int main(int argc, char *argv[]) {
    // Verifica se o nome do arquivo .txt foi fornecido como argumento
    if (argc != 2) {
        printf("Uso: %s <arquivo_de_configuracao.txt>\n", argv[0]);
        return 1;
    }

    if (!ler_configuracoes(argv[1])) return 1;

    allocate_grid();
    srand(time(NULL));
    if (!load_grid_from_file("estado_inicial.txt")) {
        printf("Inicialização aleatória será usada.\n");
        srand(time(NULL));
        init_grid();
    }
    system("clear");

    double tempo_computacao = 0.0;
    executar_simulacao(&tempo_computacao);
    salvar_tempo_em_arquivo(tempo_computacao);

    
    free_grid();

    return 0;
}
