# Nome do executável
EXEC = gol_parallel

# Arquivo de saída com tempos
TEMPOS = tempos_parallel.txt

# Cargas de trabalho (número de iterações)
CARGAS = 250 500 1000 2000 4000 8000 16000

# Número de threads a serem testados
THREADS = 1 2 3 4 5 6

# Compilador e flags para OpenMP
CC = gcc
CFLAGS = -Wall -fopenmp

# Compilação para versão paralela
$(EXEC): main.c image.c grid.c logic.c
	$(CC) -o $(EXEC) main.c image.c grid.c logic.c $(CFLAGS)

# Alvo para executar com diferentes cargas e números de threads
run: $(EXEC)
	@echo "Carga Threads Tempo(s)" > $(TEMPOS); \
	for carga in $(CARGAS); do \
		intervalo=`expr $$carga / 5`; \
		for threads in $(THREADS); do \
			echo "Executando: carga=$$carga, intervalo=$$intervalo, threads=$$threads"; \
			echo "1000 1000 $$carga $$intervalo $$threads" > config.txt; \
			OMP_NUM_THREADS=$$threads ./$(EXEC) config.txt >> $(TEMPOS); \
		done; \
	done; \
	echo "Tempos salvos em $(TEMPOS)"

# Limpeza
clean:
	rm -f $(EXEC) $(TEMPOS) config.txt *.pbm
