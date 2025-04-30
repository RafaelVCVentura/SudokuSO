# Compilador e flags
CC = gcc
CFLAGS = -Wall -Werror -g

# Arquivos fonte
SRC = main.c sudoku.c

# Nome do executável
EXEC = programa

# Alvo padrão: compila o programa
all: $(EXEC)

# Compila diretamente os arquivos .c no executável
$(EXEC): $(SRC)
	$(CC) $(CFLAGS) -o $(EXEC) $(SRC)

# Alvo para limpar o executável
clean:
	rm -f $(EXEC)
