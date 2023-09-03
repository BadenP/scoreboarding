#ifndef TRADUTOR_H
#define TRADUTOR_H

int getCodigoOpcode(const char opcode[4]);
unsigned int instrucaoParaBinario(char *buffer);
void printBinario(unsigned int num);

#endif
