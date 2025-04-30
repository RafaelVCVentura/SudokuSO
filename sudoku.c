#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <stdint.h>
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

// Recebe NULL como parâmetros caso utilize threads devido a thread que verifica as linhas não precisar receber o struct parâmetros
void *verifica_linhas(void *param) {

    int flag = (intptr_t) param;
    for (int i = 0; i < TAM_SUDOKU; i++) {
        int linha[TAM_SUDOKU]; //Cria um array com o tamanho do Sudoku
        for (int j = 0; j < TAM_SUDOKU; j++) {
            linha[j] = sudoku[i][j]; //Armazena as linhas no array 
        }
        if (verificar_segmento_valido(linha) == 0) {
            printf("Erro na linha %d\n", i);
            resultados[0] = 0; //Retorna 0 como erro e sai da thread
            if (flag == 0) {
                return NULL;
            }
            pthread_exit(NULL);
        }
    }
    resultados[0] = 1; //Retorna 1 como sucesso e sai da thread
    if(flag == 0) {
        return NULL;
    }
    pthread_exit(NULL);
}

//Recebe uma flag que indica qual é o modo do programa
void *verifica_colunas(void *param) {
    int flag = (intptr_t) param;
    /*
        Essa função funciona de forma semelhante a verificar_linhas, nela
        1º Fixamos a coluna;
        2º Iteramos sobre as linhas, então vou pegar as posições [0][0],[0][1]....
        3º Com isto, temos um array das colunas, só precisamos inverter as posições i e j da matriz (i como coluna e j como linha)
        4º Com isto, podemos passar para verificar o segmento
    */
    for( int i = 0;i < TAM_SUDOKU;i++){
        int coluna[TAM_SUDOKU];
        for(int j = 0;j < TAM_SUDOKU;j++){
            coluna[j] = sudoku[j][i];
        }
        if(verificar_segmento_valido(coluna) == 0){
            printf("Erro na coluna %d\n",i);
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

int subgrid_valido(int linha,int col){
    int visao[TAM_SUDOKU] ={0}; // Array para marcar os numeros vistos
    //Iterar sobre o grid 3x3
    for(int i =0; i<3;i++){
        for(int j = 0;j<3;j++){

            int num = sudoku[linha + i][col + j];
            if(num < 1 || num > 9 || visao[num-1]){
                return 0;
            }

            visao[num-1] = 1;
        }
    }
   
    return 1;
}

void *verifica_3x3(void*param){
    //Pega o tempo do sistema em segundos para calcular ao final
    struct timespec inicio, fim;
    clock_gettime(CLOCK_MONOTONIC, &inicio);

    parametros *data = (parametros *) param;
    int linha = data->linha;
    int coluna = data ->coluna;
    int thread_id = atomic_fetch_add(&thread_index,1);
    //Verifica o subgrid
    int valido = subgrid_valido(linha,coluna);
    // Imprime o resultado
    resultados[thread_id] = valido;
    
    //Mostra na tela quanto tempo foi necessário para rodar a subgrid 3x3
    clock_gettime(CLOCK_MONOTONIC, &fim);
    printf("O tempo necessário para verificar a thread do subgrid que começa em %d %d foi de: %.10f segundos\n",
           linha, coluna, tempo_decorrido(inicio, fim));

    free(param);
    pthread_exit(NULL);
}


void verifica_subgrids_1thread(void) {
    int index = 2;
    for(int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            parametros *data = malloc(sizeof(parametros));
            data->linha = i * 3;
            data->coluna = j * 3;

            if (subgrid_valido(data->linha, data->coluna) == 0) {
                resultados[index] = 0;
            }
            else {
                resultados[index] = 1;
            }
            index++;
        }
    }

}

//Faz a validação com uma única thread
void verifica_1thread() {
    verifica_linhas ((void*) (intptr_t) 0);
    verifica_colunas ((void*) (intptr_t) 0);
    verifica_subgrids_1thread();
}


double tempo_decorrido(struct timespec inicio, struct timespec fim) {
    return (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;
}