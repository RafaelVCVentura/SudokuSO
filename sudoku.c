#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <stdint.h>
#include "sudoku.h"

int verificar_segmento_valido(int segmento[TAM_SUDOKU]) {
    int numeros[TAM_SUDOKU + 1] = {0};
    for (int i = 0; i < TAM_SUDOKU; i++) {
        int num = segmento[i];
        if (num < 1 || num > 9 || numeros[num]) {
            printf("O número %d já existe ou é inválido\n", num);
            return 0;
        }
        numeros[num] = 1;
    }
    return 1;
}

void *verifica_linha_individual(void *param) {
    parametros *data = (parametros *)param;
    int linha_num = data->linha;
    int thread_id = data->thread_id;
    int linha[TAM_SUDOKU];
    
    for (int j = 0; j < TAM_SUDOKU; j++) {
        linha[j] = sudoku[linha_num][j];
    }
    
    resultados[thread_id] = verificar_segmento_valido(linha);
    
    free(param);
    pthread_exit(NULL);
}

void *verifica_coluna_individual(void *param) {
    parametros *data = (parametros *)param;
    int coluna_num = data->coluna;
    int thread_id = data->thread_id;
    int coluna[TAM_SUDOKU];
    
    for (int i = 0; i < TAM_SUDOKU; i++) {
        coluna[i] = sudoku[i][coluna_num];
    }
    
    resultados[thread_id] = verificar_segmento_valido(coluna);
    
    free(param);
    pthread_exit(NULL);
}

void *verifica_linhas(void *param) {
    int flag = (intptr_t) param;
    for (int i = 0; i < TAM_SUDOKU; i++) {
        int linha[TAM_SUDOKU];
        for (int j = 0; j < TAM_SUDOKU; j++) {
            linha[j] = sudoku[i][j];
        }
        if (verificar_segmento_valido(linha) == 0) {
            printf("Erro na linha %d\n", i);
            resultados[0] = 0;
            if (flag == 0) {
                return NULL;
            }
            pthread_exit(NULL);
        }
    }
    resultados[0] = 1;
    if (flag == 0) {
        return NULL;
    }
    pthread_exit(NULL);
}

void *verifica_colunas(void *param) {
    int flag = (intptr_t) param;
    for (int i = 0; i < TAM_SUDOKU; i++) {
        int coluna[TAM_SUDOKU];
        for (int j = 0; j < TAM_SUDOKU; j++) {
            coluna[j] = sudoku[j][i];
        }
        if (verificar_segmento_valido(coluna) == 0) {
            printf("Erro na coluna %d\n", i);
            resultados[1] = 0;
            if (flag == 0) {
                return NULL;
            }
            pthread_exit(NULL);
        }
    }
    resultados[1] = 1;
    if (flag == 0) {
        return NULL;
    }
    pthread_exit(NULL);
}

int subgrid_valido(int linha, int col) {
    int visao[TAM_SUDOKU] = {0};
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int num = sudoku[linha + i][col + j];
            if (num < 1 || num > 9 || visao[num-1]) {
                return 0;
            }
            visao[num-1] = 1;
        }
    }
    return 1;
}

void *verifica_3x3(void *param) {
    parametros *data = (parametros *)param;
    int linha = data->linha;
    int coluna = data->coluna;
    int thread_id = data->thread_id;
    
    printf("Iniciando verificação do subgrid (%d,%d)\n", linha, coluna);
    
    struct timespec inicio, fim;
    clock_gettime(CLOCK_MONOTONIC, &inicio);
    
    int valido = subgrid_valido(linha, coluna);
    
    resultados[thread_id] = valido;
    
    clock_gettime(CLOCK_MONOTONIC, &fim);
    printf("Verificação do subgrid (%d,%d) concluída: %d\n", linha, coluna, valido);

    free(param);
    pthread_exit(NULL);
}

void verifica_subgrids_1thread(void) {
    int index = 2;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            parametros *data = malloc(sizeof(parametros));
            if (!data) {
                perror("Erro ao alocar memória para parâmetros");
                exit(EXIT_FAILURE);
            }
            data->linha = i * 3;
            data->coluna = j * 3;
            resultados[index++] = subgrid_valido(data->linha, data->coluna);
            free(data);
        }
    }
}

void verifica_1thread() {
    verifica_linhas((void*)(intptr_t)0);
    verifica_colunas((void*)(intptr_t)0);
    verifica_subgrids_1thread();
}

double tempo_decorrido(struct timespec inicio, struct timespec fim) {
    return (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;
}