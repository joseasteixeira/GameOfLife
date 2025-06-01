#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include "gol.h"

int max_iter = 0;
int intervalo = 0;

int num_threads = 1;

// Lê os parâmetros do arquivo de configuração (.txt)
int ler_configuracoes(const char *arquivo) {
    FILE *config = fopen(arquivo, "r");
    if (!config) {
        perror("Erro ao abrir arquivo de configuração");
        return 0;
    }

    // Ler os valores.
    if (fscanf(config, "%d %d %d %d %d", &WIDTH, &HEIGHT, &max_iter, &intervalo, &num_threads) != 5) {
        printf("Erro: O arquivo deve conter quatro números inteiros: WIDTH HEIGHT ITERACOES INTERVALO num_threads\n");
        fclose(config);
        return 0;
    }

    fclose(config);

    // Verifica se os valores são validos.
    if (WIDTH <= 0 || HEIGHT <= 0 || max_iter <= 0 || intervalo <= 0 || num_threads <= 0) {
        printf("Erro: Todos os parâmetros devem ser positivos.\n");
        return 0;
    }

    return 1;
}

// Executa o loop principal do Jogo da Vida
double executar_simulacao(void) {
    double tempo_total_inicio = omp_get_wtime();
    double tempo_save_total = 0.0;

    for (int i = 0; i < max_iter; i++) {
        if ((i + 1) % intervalo == 0) {
            double inicio_save = omp_get_wtime();
            save_pbm(grid, HEIGHT, WIDTH, i + 1);
            double fim_save = omp_get_wtime();

            tempo_save_total += (fim_save - inicio_save);
        }

        gen_next();
    }

    double tempo_total_fim = omp_get_wtime();

    // Retorna tempo total de computação sem contar o tempo de salvar imagem
    return (tempo_total_fim - tempo_total_inicio - tempo_save_total);
}



// Salva um arquivo de texto com o tempo de execução em segundos.
void salvar_tempo(double tempo) {
    FILE *arquivo = fopen("tempos_parallel.txt", "a");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo para salvar tempo da gen_next");
        return;
    }
    fprintf(arquivo, "Tempo gen_next: %.6f\n", tempo);
    fclose(arquivo);
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

    omp_set_num_threads(num_threads);

    double tempo = executar_simulacao(); 
    salvar_tempo(tempo);

    
    free_grid();

    return 0;
}
