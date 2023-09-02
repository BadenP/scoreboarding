#include <stdio.h>
#include <stdlib.h>
#include "barramento.h"

int barramento;

void colocaBarramento(int valor){
    barramento=valor;
}
unsigned int pegaBarramento(int barramento){
    return barramento;
}