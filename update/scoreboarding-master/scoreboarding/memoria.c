#include <stdio.h>
#include <stdlib.h>
#include "memoria.h"
#include "tradutor.h"
#include "registradores.h"

int *memoria;
int tam;
int qtdeInsts;

void inicializaMemoria(int m){
    if(m<=100){
        printf("Tamanho de memória insuficiente. O tamanho da memória deve ser mair do que 100. \n");
    }
    else{
        memoria = (int*)malloc(sizeof(int) * m * 4);
        tam=m*4;
    }
}

void printMemoria(){
    printf("Conteúdo da memória:\n");
    for (int i = 0; i < tam; i = i+4) {
        printf("Endereço %d: %d\n", i/4, memoria[i]);
    }
}

void insereMemoria(int instrucao){
    if(memoria==NULL){
        printf("Erro.");
    }
    else{
        memoria[pc]=instrucao;
    }
}
