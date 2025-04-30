
# SudokuSO

Projeto final da disciplina de **Sistemas Operacionais** (período 2024.2), da **Universidade Federal da Paraíba (UFPB)**.

Este projeto implementa uma solução para o problema **"Sudoku Solution Validator"**, conforme proposto no livro _Operating System Concepts_ (10ª edição), de **Abraham Silberschatz, Peter Baer Galvin e Greg Gagne**.

Como adicional, foi introduzido o modo de execução com apenas 1 Thread (modo 1), sendo assim, temos o modo 1 e o 2, sendo o 2 o modo de execução com 11 threads.

Além disso foi adicionado um retorno de tempo de execução, tanto de cada thread como o tempo total de execução do programa.

---

## 📦 Estrutura do Projeto

- `main.c`: Arquivo principal que gerencia a execução.
- `sudoku.c`: Contém a lógica de verificação do Sudoku.
- `sudoku.h`: Declarações e definições usadas no projeto.

---

## ⚙️ Como Compilar

Compile o projeto usando o comando:

```bash
make
```

Caso o make não esteja do agrado do usuário, é possível compilar o projeto usando o comando:

```bash
gcc main.c sudoku.c -o programa
```

Isso irá gerar o executável chamado `programa`.

---

## ▶️ Como Executar

Após a compilação, execute o programa passando o arquivo de teste como argumento:

```bash
./programa nome_arquivo_sudoku_teste.txt modo_de_execucao(1 ou 2)
```

### Exemplo:
```bash
./programa teste.txt 1
```

---

## 🧰 Requisitos

- Compilador `gcc`
- Ambiente Linux ou compatível com POSIX
- Download do comando `make` no Linux
