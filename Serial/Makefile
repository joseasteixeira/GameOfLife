# Nome do executável
EXEC = gol

# Arquivo de saída com tempos
TEMPOS = tempos_serial.txt

# Cargas de trabalho (número de iterações)
CARGAS = 250 500 1000 2000 4000 8000 16000

# Compilador e flags
CC = gcc
CFLAGS = -Wall -O3

# Compilação
$(EXEC): main.c image.c grid.c logic.c
	$(CC) -o $(EXEC) main.c image.c grid.c logic.c $(CFLAGS)

# Alvo para executar com diferentes cargas
run: $(EXEC)
	@rm -f $(TEMPOS)               # Remove arquivo antigo
	@echo "Carga Tempo(s)" > $(TEMPOS)  # Cabeçalho
	@for carga in $(CARGAS); do \
		intervalo=$$((carga / 5)); \
		echo "1000 1000 $$carga $$intervalo 4" > config.txt; \
		./$(EXEC) config.txt; \
	done
# Limpeza
clean:
	rm -f $(EXEC) $(TEMPOS) config.txt *.pbm

