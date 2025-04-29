#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include "sudoku.h"

// Recebe um array de inteiros (seja uma linha, coluna, ou subgrade 3x3)
int verificar_segmento_valido(int segmento[TAM_SUDOKU]) {
    int numeros[TAM_SUDOKU + 1] = {0}; // Cria um array de tamanho 10 para colocar cada número em seu índice (ex: numeros[1] = 1), o último índice não é usado
    for (int i = 0; i < TAM_SUDOKU; i++) {
        int num = segmento[i]; 
        //Verifica se o sudoku tem dígitos de 0 a 9 ou se o número já apareceu
        if (num < 1 || num > 9 || numeros[num]) {
            printf("O número %d já existe ou é inválido\n", num);
            return 0;
        }
        numeros[num] = 1; // Salva no array numeros que o numero ja foi encontrado
    }
    return 1; 
}

// Recebe NULL como parâmetros devido a thread que verifica as linhas não precisar receber o struct parâmetros
void *verifica_linhas(void *param) {
    for (int i = 0; i < TAM_SUDOKU; i++) {
        int linha[TAM_SUDOKU]; //Cria um array com o tamanho do Sudoku
        for (int j = 0; j < TAM_SUDOKU; j++) {
            linha[j] = sudoku[i][j]; //Armazena as linhas no array 
        }
        if (verificar_segmento_valido(linha) == 0) {
            printf("Erro na linha %d\n", i);
            resultados[0] = 0; //Retorna 0 como erro e sai da thread
            pthread_exit(NULL);
        }
    }
    resultados[0] = 1; //Retorna 1 como sucesso e sai da thread
    pthread_exit(NULL);
}

void *verifica_colunas(void *parametros) {
}
