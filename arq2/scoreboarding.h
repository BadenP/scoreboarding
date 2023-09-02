#ifndef SCOREBOARDING_H
#define SCOREBOARDING_H

//void statusInstrucoes();
void statusRegistradores();
void statusUFs();
extern statusInstrucoes statusI;

typedef struct{
    int instrucao;
    int busca;
    int emissao;
    int leitura_op;
    int execucao;
    int escrita;
}statusInstrucoes;

#endif