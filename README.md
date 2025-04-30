
# SudokuSO

Projeto final da disciplina de **Sistemas Operacionais** (período 2024.2), da **Universidade Federal da Paraíba (UFPB)**.

Este projeto implementa uma solução para o problema **"Sudoku Solution Validator"**, conforme proposto no livro _Operating System Concepts_ (10ª edição), de **Abraham Silberschatz, Peter Baer Galvin e Greg Gagne**.

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

Isso irá gerar o executável chamado `programa`.

---

## ▶️ Como Executar

Após a compilação, execute o programa passando o arquivo de teste como argumento:

```bash
./programa nome_arquivo_sudoku_teste.txt
```

### Exemplo:
```bash
./programa teste.txt
```

---

## 🧰 Requisitos

- Compilador `gcc`
- Ambiente Linux ou compatível com POSIX
- Download do comando `make` no Linux
