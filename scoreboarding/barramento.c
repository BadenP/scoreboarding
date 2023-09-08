#include <stdio.h>
#include <stdlib.h>
#include "barramento.h"

int barramento;
int barramentoResultados;

void colocaBarramento(int valor){
    barramento=valor;
}

int pegaBarramento(){
    return barramento;
}

void colocaBarramentoResultados(int valor){
    barramentoResultados=valor;
}

int pegaBarramentoResultados(){
    return barramentoResultados;
}