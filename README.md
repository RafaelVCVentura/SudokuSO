# SudokuSO
Projeto final da disciplina de Sistemas Operacionais no período 2024.2, na Universidade Federal da Paraíba (UFPB). Neste projeto desenvolvemos uma solução para o \"Sudoku Solution Validator\", disponível no livro \"Operating System Concepts 10th edition\", dos autores Abraham Silberschatz, Peter Baer Galvin e Greg Gagne.

## Como Compilar
Compile os arquivos `main.c` e `sudoku.c` para o arquivo de saída desejado utilizando o `gcc`:```bash\ngcc main.c sudoku.c -o sudokuSO\n```\
## Como Executar
Após compilar, execute o programa passando o arquivo de teste como argumento:``bash\n./sudokuSO nome_arquivo_sudoku_teste.txt\n```\n\nExemplo:\n\n```bash\n./sudokuSO teste1.txt\n```\n\n## Estrutura do Projeto\n\n- `main.c`: Arquivo principal que gerencia a execução.\n- `sudoku.c`: Contém a lógica de verificação do Sudoku.\n- `sudoku.h`: Definições e declarações usadas no projeto.\n\n## Requisitos\n\n- Compilador `gcc`\n- Ambiente Linux ou similar