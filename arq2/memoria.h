#ifndef MEMORIA_H
#define MEMORIA_H

extern int qtdeInsts;
extern int tam;
extern int *memoria;
void inicializaMemoria(int m);
void insereMemoria(int instrucao);
void printMemoria();

#endif
