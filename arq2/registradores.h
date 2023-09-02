#ifndef REGISTRADORES_H
#define REGISTRADORES_H

#include <stdio.h>
#include <stdlib.h>

extern unsigned int bancoRegs[32];
extern int pc;

void escreverRegistrador();
void lerRegistrador();

#endif 