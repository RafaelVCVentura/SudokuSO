#ifndef SUDOKU_H
#define SUDOKU_H
#include <stdlib.h>
#include <pthread.h>
#include <stdatomic.h>
#define NUM_THREADS 27
#define TAM_SUDOKU 9

extern int resultados[27];
extern pthread_t threads[27];
extern atomic_int thread_index;
extern int sudoku[TAM_SUDOKU][TAM_SUDOKU];

typedef struct {
    int linha;
    int coluna;
} parametros;

void* verifica_linhas(void* parametros);
void* verifica_colunas(void* parametros);
void* verifica_linha_individual(void* parametros);
void* verifica_coluna_individual(void* parametros);
void* verifica_3x3(void* parametros);
void verifica_subgrids_1thread(void);
int verificar_segmento_valido(int segmento[TAM_SUDOKU]);
void verifica_1thread();
double tempo_decorrido(struct timespec inicio, struct timespec fim);
#endif