#include <stdio.h>
#include <stdlib.h>
#include "memoria.h"
#include "tradutor.h"
#include "common.h"
unsigned int *memoria;

void inicializaMemoria(int m){
    memoria = (unsigned int*)malloc(sizeof(unsigned int) * m);
}#include <stdio.h>
#include <stdlib.h>
#include "memoria.h"
#include "tradutor.h"
#include "common.h"
unsigned int *memoria;

void inicializaMemoria(int m){
    memoria = (unsigned int*)malloc(sizeof(unsigned int) * m);
}

void insereMemoria(unsigned int instrucao){
    if(memoria==NULL){
        printf("Erro.");
    }
    else{
        memoria[pc++]=instrucao;
    }
}

void printMemoria(int memsize){
    for(int i=0; i<memsize; i++){
        printf("\n%u", memoria[i]);
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
