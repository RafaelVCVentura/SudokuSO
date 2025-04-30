
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

## 📚 Planilha
https://docs.google.com/spreadsheets/d/1V2LT24aXL6VpNf5aa6G5U7vmZ9EdaKgSjE_nBTlmVoY/edit?usp=sharing

## 🧰 Requisitos

- Compilador `gcc` em uma versão compatível com `C11`
- Ambiente Linux ou compatível com POSIX
- Download do comando `make` no Linux

---

## 👥 Autores e Contribuições

- **Matheus Yago Lima de Freitas**  
  Responsável pela criação e leitura do arquivo de entrada, além da lógica principal de validação do Sudoku. Implementou funções para verificação de linhas, subgrids 3x3 e colunas no modo com 11 threads. Também estruturou a criação das threads, desenvolveu o `Makefile` e configurou o workflow do GitHub Actions.

- **Rafael Victor Costa Ventura**  
  Atuou na organização do código, criando a estrutura do TAD (structs e funções) e a implementação da `main`. Desenvolveu o modo de execução com uma thread, além das funções de verificação de colunas e subgrids. Implementou a medição do tempo de execução e o uso de variáveis atômicas para tratar problemas de concorrência.

- **Candido Queiroga**  
  Responsável pela criação e implementação do modo com 27 threads. Também analisou os dados de tempo de execução coletados, organizando-os em uma planilha para comparação entre os diferentes modos de execução.
