#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include "gol.h"

int max_iter = 0;
int intervalo = 0;
int num_threads = 0;  // Variável para armazenar o número de threads

// Lê os parâmetros do arquivo de configuração (.txt)
int ler_configuracoes(const char *nome_arquivo) {
    FILE *config = fopen(nome_arquivo, "r");
    if (!config) {
        perror("Erro ao abrir arquivo de configuração");
        return 0;
    }

    // Ler os valores: WIDTH, HEIGHT, ITERACOES, INTERVALO e THREADS
    if (fscanf(config, "%d %d %d %d %d", &WIDTH, &HEIGHT, &max_iter, &intervalo, &num_threads) != 5) {
        printf("Erro: O arquivo deve conter cinco números inteiros: WIDTH HEIGHT ITERACOES INTERVALO THREADS\n");
        fclose(config);
        return 0;
    }

    fclose(config);

    // Verifica se os valores são válidos.
    if (WIDTH <= 0 || HEIGHT <= 0 || max_iter <= 0 || intervalo <= 0 || num_threads <= 0) {
        printf("Erro: Todos os parâmetros devem ser positivos.\n");
        return 0;
    }

    return 1;
}

// Executa o loop principal do Jogo da Vida
void executar_simulacao(void) {
    for (int i = 0; i < max_iter; i++) {
        if ((i + 1) % intervalo == 0) {
            save_pbm(grid, HEIGHT, WIDTH, i + 1);
        }
        gen_next();
    }
}

// Função para salvar o tempo em um arquivo
void salvar_tempo(double tempo_real) {
    FILE *arquivo = fopen("tempos_parallel.txt", "a");  // Abrir no modo de append
    if (!arquivo) {
        perror("Erro ao abrir o arquivo para salvar o tempo");
        return;
    }
    // Salva o tempo real de execução no arquivo
    fprintf(arquivo, " %d, %.2f \n",num_threads, tempo_real);
    fclose(arquivo);
}

int main(int argc, char *argv[]) {
    // Verifica se o nome do arquivo .txt foi fornecido como argumento
    if (argc != 2) {
        printf("Uso: %s <arquivo_de_configuracao.txt>\n", argv[0]);
        return 1;
    }

    if (!ler_configuracoes(argv[1])) return 1;

    // Configura o número de threads conforme lido no arquivo
    omp_set_num_threads(num_threads);

    allocate_grid();
    srand(time(NULL));
    init_grid();
    system("clear");

    double start_real = omp_get_wtime();
    executar_simulacao();
    double end_real = omp_get_wtime();
    double tempo_real = end_real - start_real;

    salvar_tempo(tempo_real);

    free_grid();

    return 0;
}
