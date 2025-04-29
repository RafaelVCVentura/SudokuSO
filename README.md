# SudokuSO
Projeto final da disciplina de Sistemas Operacionais no período 2024.2, na Universidade Federal da Paraíba (UFPB). Neste projeto desenvolvemos uma solução para o \"Sudoku Solution Validator\", disponível no livro \"Operating System Concepts 10th edition\", dos autores Abraham Silberschatz, Peter Baer Galvin e Greg Gagne.

## Como Compilar
Compile os arquivos `main.c` e `sudoku.c` para o arquivo de saída desejado utilizando o `gcc`:```bash gcc main.c sudoku.c -o sudokuSO```
## Como Executar
Após compilar, execute o programa passando o arquivo de teste como argumento:``bash\n./sudokuSO nome_arquivo_sudoku_teste.txt\n```\n\nExemplo:```bash./sudokuSO teste1.txt```
## Estrutura do Projeto 
- `main.c`: Arquivo principal que gerencia a execução.
- `sudoku.c`: Contém a lógica de verificação do Sudoku.
- `sudoku.h`: Definições e declarações usadas no projeto.
## Requisitos
- Compilador `gcc`- Ambiente Linux ou similar