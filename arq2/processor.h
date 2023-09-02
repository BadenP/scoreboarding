#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "barramento.h"
#include "unidade_funcional.h"
#include "scoreboarding.h"
#include "registradores.h"
#include "memoria.h"

typedef struct {
    unsigned int busca;
    unsigned int emissao;
    unsigned int leitura_op;
    conjuntoUFS execucao;
    unsigned int escrita;
}pipeline;

extern pipeline pipe;

void inicializaPipeline(int add, int mul, int inteiro);
int buscaInstrucao(pipeline pipe, int pc, int barramento);
unsigned int getOpcode(unsigned int instrucao);
unsigned int getRegistradorDestino(unsigned int instrucao);
unsigned int getRegistradorFonte1(unsigned int instrucao);
unsigned int getRegistradorFonte2(unsigned int instrucao);
void emiteInstrucao(pipeline *pipe, conjuntoUFS *UFS);
void leituraOperandos(pipeline *pipe);
void executaInstrucao(pipeline *pipe);

#endif 
