#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include "sudoku.h"

#define NUM_THREADS 11
#define TAM_SUDOKU 9

int sudoku[TAM_SUDOKU][TAM_SUDOKU];





int ler_sudoku(const char *nome_arquivo, int matriz[TAM_SUDOKU][TAM_SUDOKU]) {
    /*Para esta função é passado o nome do arquivo do jogo sudoku + extensão, que são obtidos pelo argumento na segunda posição argv
     e também uma matriz alocada TAM_SUDOKUxTAM_SUDOKU
    */
    FILE *fp = fopen(nome_arquivo, "r");
    if (!fp) {
        perror("Erro ao abrir o arquivo");
        return 0;  // Falha
    }
    // Lê os valores do arquivo preenchendo a matriz linha por linha
    for (int i = 0; i < TAM_SUDOKU; i++) {
        for (int j = 0; j < TAM_SUDOKU; j++) {
            // Lê um inteiro do arquivo; se falhar, exibe erro e retorna falha
            if (fscanf(fp, "%d", &matriz[i][j]) != 1) 
            {
                fprintf(stderr, "Erro ao ler valor da matriz.\n");
                fclose(fp);
                return 0;
            }
        }
    }
    // Fecha o arquivo após a leitura
    fclose(fp);
    return 1;  // Sucesso
}
void *verificarLinha(void *arg) {
    int linha = *(int *)arg;
    int numeros[10] = {0};

    for (int j = 0; j < TAM_SUDOKU; j++) {
        int num = sudoku[linha][j];
        if (num < 1 || num > 9) {
            printf("Linha %d possui número inválido: %d\n", linha + 1, num);
            pthread_exit((void *)0);
        }
        if (numeros[num]) {
            printf("Linha %d possui número repetido: %d\n", linha + 1, num);
            pthread_exit((void *)0);
        }
        numeros[num] = 1;
    }

    pthread_exit((void *)1);
}



int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("Uso: %s <nome_do_arquivo>\n", argv[0]);
        return 1;
    }

    if (!ler_sudoku(argv[1], sudoku)) {
        return 1; // Erro já tratado dentro da função
    }

    printf("Matriz Sudoku lida:\n");
    for (int i = 0; i < TAM_SUDOKU; i++) {
        for (int j = 0; j < TAM_SUDOKU; j++) {
            printf("%d ", sudoku[i][j]);
        }
        printf("\n");
    }



    return 0;
}
