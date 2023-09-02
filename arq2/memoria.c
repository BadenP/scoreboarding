#include <stdio.h>
#include <stdlib.h>
#include "memoria.h"
#include "tradutor.h"
#include "registradores.h"

unsigned int *memoria;
int tam;

void inicializaMemoria(int m){
    if(m<=100){
        printf("Tamanho de memória insuficiente. O tamanho da memória deve ser mair do que 100. \n");
    }
    else{
        memoria = (unsigned int*)malloc(sizeof(unsigned int) * m);
        tam=m;
    }
}

void printMemoria(){
    printf("Conteúdo da memória:\n");
    for (int i = 0; i < tam; i++) {
        printf("Endereço %d: %u\n", i, memoria[i]);
    }
}

void insereMemoria(unsigned int instrucao){
    if(memoria==NULL){
        printf("Erro.");
    }
    else{
        memoria[pc]=instrucao;
    }
}
