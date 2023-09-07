#ifndef SCOREBOARDING_H
#define SCOREBOARDING_H

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

extern statusInstrucoes *statusI;
void printStatusInstrucoes();
void inicializaStatusInstrucoes();
int getIndiceInstrucao(int instrucao);

#endif