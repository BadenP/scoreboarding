#ifndef MEMORIA_H
#define MEMORIA_H

extern int qtdeInsts;
extern int tam;
extern long int *memoria;
void inicializaMemoria(int m);
void insereMemoria(long int instrucao);
void printMemoria();

#endif
