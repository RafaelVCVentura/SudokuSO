#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include "sudoku.h"
#define NUM_THREADS 11
#define TAM_SUDOKU 9

int resultados[11] = {0};
pthread_t threads[11];
int sudoku[TAM_SUDOKU][TAM_SUDOKU];
atomic_int thread_index = 2;

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
            // Lê um inteiro do arquivo e se o caractere é um número; se falhar, exibe erro e retorna falha
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

void cria_threads () {
    pthread_create(&threads[0], NULL, verifica_linhas, NULL);
    pthread_create(&threads[1],NULL,verifica_colunas,NULL);
    int index = 2;
    for(int i =0; i < 3;i++){
        for(int j = 0;j<3;j++){
            parametros *data = malloc(sizeof(parametros));
            data->linha = i *3;
            data->coluna = j*3;

            if(pthread_create(&threads[index],NULL,verifica_3x3,data)!=0){
                perror("Erro ao criar thread de subgrid");
                exit(EXIT_FAILURE);
            }
            index++;
        }
    }
}

void aguarda_threads() {
    for(int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
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

    cria_threads();
    aguarda_threads();
    for(int i = 0; i <NUM_THREADS;i++){
        printf("%d resultado [%d]\n", resultados[i],i);
    }
    

    return 0;
}
