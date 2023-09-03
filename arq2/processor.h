#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "barramento.h"
#include "unidade_funcional.h"
#include "scoreboarding.h"
#include "registradores.h"
#include "memoria.h"

void inicializaPipeline(int add, int mul, int inteiro);
unsigned int getOpcode(unsigned int instrucao);
unsigned int getRegistradorDestino(unsigned int instrucao);
unsigned int getRegistradorFonte1(unsigned int instrucao);
unsigned int getRegistradorFonte2(unsigned int instrucao);
void emiteInstrucao();
void buscaInstrucao();
void leituraDeOperandos();
void execucao();
void executaInstrucao(int destino, int fonte1, int fonte2, int opcode);

#endif 
