#ifndef SCOREBOARDING_H
#define SCOREBOARDING_H
#include "unidade_funcional.h"
void statusRegistradores();
void statusUFs();

typedef struct{
    int instrucao;
    int busca;
    int emissao;
    int leitura_op;
    int execucao;
    int escrita;
}statusInstrucoes;

extern char* statusReg[32];
extern statusInstrucoes *statusI;
void printStatusInstrucoes();
void inicializaStatusInstrucoes();

#endif
