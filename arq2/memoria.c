#include <stdio.h>
#include <stdlib.h>
#include "memoria.h"
#include "tradutor.h"
#include "registradores.h"

long int *memoria;
int tam;
int qtdeInsts;

void inicializaMemoria(int m){
    if(m<=100){
        printf("Tamanho de memória insuficiente. O tamanho da memória deve ser mair do que 100. \n");
    }
    else{
        memoria = (long int*)malloc(sizeof(long int) * m);
        tam=m;
    }
}

void printMemoria(){
    printf("Conteúdo da memória:\n");
    for (int i = 0; i < tam; i = i+4) {
        printf("Endereço %d: %ld\n", i, memoria[i]);
    }
}

void insereMemoria(long int instrucao){
    if(memoria==NULL){
        printf("Erro.");
    }
    else{
        memoria[pc]=instrucao;
    }
}
