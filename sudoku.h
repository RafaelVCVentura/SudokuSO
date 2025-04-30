#ifndef SUDOKU_H
#define SUDOKU_H
#include <stdlib.h>
#include <pthread.h>
#include <stdatomic.h>
#define NUM_THREADS 11
#define TAM_SUDOKU 9

extern int resultados[11];
extern pthread_t threads[11];
extern atomic_int thread_index;
extern int sudoku[TAM_SUDOKU][TAM_SUDOKU];

typedef struct {
    int linha;
    int coluna;
} parametros;

void* verifica_linhas(void* parametros);
void* verifica_colunas(void* parametros);
void* verifica_3x3(void* parametros);
void verifica_subgrids_1thread(void);
int verificar_segmento_valido(int segmento[TAM_SUDOKU]);
void verifica_1thread();
double tempo_decorrido(struct timespec inicio, struct timespec fim);
#endif 