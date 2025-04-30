#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>
#include <time.h>
#include <string.h>
#include "sudoku.h"

#define NUM_THREADS 27
#define TAM_SUDOKU 9

int resultados[27] = {0};
pthread_t threads[27];
int sudoku[TAM_SUDOKU][TAM_SUDOKU];
atomic_int thread_index = 0;

int ler_sudoku(const char *nome_arquivo, int matriz[TAM_SUDOKU][TAM_SUDOKU]) {
    FILE *fp = fopen(nome_arquivo, "r");
    if (!fp) {
        perror("Erro ao abrir o arquivo");
        return 0;
    }
    for (int i = 0; i < TAM_SUDOKU; i++) {
        for (int j = 0; j < TAM_SUDOKU; j++) {
            if (fscanf(fp, "%d", &matriz[i][j]) != 1) {
                fprintf(stderr, "Erro ao ler valor da matriz.\n");
                fclose(fp);
                return 0;
            }
            // Validar o valor lido
            if (matriz[i][j] < 1 || matriz[i][j] > 9) {
                fprintf(stderr, "Valor inválido encontrado na posição (%d,%d): %d\n", i, j, matriz[i][j]);
                fclose(fp);
                return 0;
            }
        }
    }
    fclose(fp);
    return 1;
}

void cria_threads_11() {
    struct timespec inicio, fim;
    
    // Linhas
    clock_gettime(CLOCK_MONOTONIC, &inicio);
    if (pthread_create(&threads[0], NULL, verifica_linhas, (void*)(intptr_t)1) != 0) {
        perror("Erro ao criar thread de linhas");
        exit(EXIT_FAILURE);
    }
    clock_gettime(CLOCK_MONOTONIC, &fim);
    printf("\nTempo para criar thread de linhas: %.10f segundos\n", tempo_decorrido(inicio, fim));

    // Colunas
    clock_gettime(CLOCK_MONOTONIC, &inicio);
    if (pthread_create(&threads[1], NULL, verifica_colunas, (void*)(intptr_t)1) != 0) {
        perror("Erro ao criar thread de colunas");
        exit(EXIT_FAILURE);
    }
    clock_gettime(CLOCK_MONOTONIC, &fim);
    printf("Tempo para criar thread de colunas: %.10f segundos\n", tempo_decorrido(inicio, fim));

    // Subgrids
    printf("\nTempos de execução dos subgrids:\n");
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
            data->thread_id = index; // Índice para resultados (2 a 10 para subgrids)
            
            clock_gettime(CLOCK_MONOTONIC, &inicio);
            if (pthread_create(&threads[index], NULL, verifica_3x3, data) != 0) {
                perror("Erro ao criar thread de subgrid");
                free(data);
                exit(EXIT_FAILURE);
            }
            clock_gettime(CLOCK_MONOTONIC, &fim);
            printf("Subgrid (%d,%d) - tempo criação: %.10f segundos\n", 
                  data->linha, data->coluna, tempo_decorrido(inicio, fim));
            
            index++;
        }
    }
}

void cria_threads_27() {
    // Criação da thread para cada linha
    for (int i = 0; i < TAM_SUDOKU; i++) {
        struct timespec inicio, fim;
        clock_gettime(CLOCK_MONOTONIC, &inicio);
        
        parametros *data = malloc(sizeof(parametros));
        if (!data) {
            perror("Erro ao alocar memória para parâmetros");
            exit(EXIT_FAILURE);
        }
        data->linha = i;
        data->coluna = 0; // Não usado
        data->thread_id = i; // Índice para resultados (0 a 8 para linhas)
        if (pthread_create(&threads[i], NULL, verifica_linha_individual, data) != 0) {
            perror("Erro ao criar thread de linha");
            free(data);
            exit(EXIT_FAILURE);
        }
        
        clock_gettime(CLOCK_MONOTONIC, &fim);
        printf("Tempo para linha %d: %.10f segundos\n", i, tempo_decorrido(inicio, fim));
    }
    printf("\n");
    // Criação da thread para cada coluna
    for (int j = 0; j < TAM_SUDOKU; j++) {
        struct timespec inicio, fim;
        clock_gettime(CLOCK_MONOTONIC, &inicio);
        
        parametros *data = malloc(sizeof(parametros));
        if (!data) {
            perror("Erro ao alocar memória para parâmetros");
            exit(EXIT_FAILURE);
        }
        data->linha = 0; // Não usado
        data->coluna = j;
        data->thread_id = TAM_SUDOKU + j; // Índice para resultados (9 a 17 para colunas)
        if (pthread_create(&threads[TAM_SUDOKU + j], NULL, verifica_coluna_individual, data) != 0) {
            perror("Erro ao criar thread de coluna");
            free(data);
            exit(EXIT_FAILURE);
        }
        
        clock_gettime(CLOCK_MONOTONIC, &fim);
        printf("Tempo para coluna %d: %.10f segundos\n", j, tempo_decorrido(inicio, fim));
    }
    printf("\n");
    // Criação da thread para cada subgrid 3x3
    int index = TAM_SUDOKU * 2; // Começa em 18
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            struct timespec inicio, fim;
            clock_gettime(CLOCK_MONOTONIC, &inicio);
            
            parametros *data = malloc(sizeof(parametros));
            if (!data) {
                perror("Erro ao alocar memória para parâmetros");
                exit(EXIT_FAILURE);
            }
            data->linha = i * 3;
            data->coluna = j * 3;
            data->thread_id = index; // Índice para resultados (18 a 26 para subgrids)
            if (pthread_create(&threads[index], NULL, verifica_3x3, data) != 0) {
                perror("Erro ao criar thread de subgrid");
                free(data);
                exit(EXIT_FAILURE);
            }
            
            clock_gettime(CLOCK_MONOTONIC, &fim);
            printf("Tempo para subgrid (%d,%d): %.10f segundos\n", 
                   data->linha, data->coluna, tempo_decorrido(inicio, fim));
            
            index++;
        }
    }
}

void aguarda_threads(int num_threads) {
    for (int i = 0; i < num_threads; i++) {
        if (threads[i]) {
            pthread_join(threads[i], NULL);
        }
    }
}

int main(int argc, char *argv[]) {
    // Inicializar threads com zero
    memset(threads, 0, sizeof(pthread_t) * NUM_THREADS);

    if (argc < 3) {
        printf("Uso: %s <nome_do_arquivo> <modo>\n", argv[0]);
        printf("Modos disponíveis:\n");
        printf("1 - 1 thread\n");
        printf("2 - 11 threads\n");
        printf("3 - 27 threads\n");
        return 1;
    }

    int escolha = atoi(argv[2]);
    struct timespec inicio_total, fim_total;
    clock_gettime(CLOCK_MONOTONIC, &inicio_total);

    if (!ler_sudoku(argv[1], sudoku)) {
        return 1;
    }

    int num_threads = 0;
    switch (escolha) {
        case 1:
            verifica_1thread();
            num_threads = 0; // Nenhuma thread criada
            break;
        case 2:
            cria_threads_11();
            num_threads = 11; // 1 para linhas, 1 para colunas, 9 para subgrids
            aguarda_threads(num_threads);
            break;
        case 3:
            cria_threads_27();
            num_threads = 27; // 9 para linhas, 9 para colunas, 9 para subgrids
            aguarda_threads(num_threads);
            break;
        default:
            printf("Modo inválido! Escolha 1, 2 ou 3.\n");
            return 1;
    }

    printf("\nMatriz Sudoku lida:\n");
    for (int i = 0; i < TAM_SUDOKU; i++) {
        for (int j = 0; j < TAM_SUDOKU; j++) {
            printf("%d ", sudoku[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    
    int threads_verificadas = (escolha == 1) ? 11 : (escolha == 2) ? 11 : 27;
    for (int i = 0; i < threads_verificadas; i++) {
        if (resultados[i] == 0) {
            printf("O Sudoku é inválido.\n");
            return 1;
        }
    }
    printf("O sudoku é válido!\n");

    clock_gettime(CLOCK_MONOTONIC, &fim_total);
    printf("O tempo de execução total foi de: %.10f segundos\n", tempo_decorrido(inicio_total, fim_total));
    return 0;
}