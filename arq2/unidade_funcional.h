#ifndef UNIDADE_FUNCIONAL_H
#define UNIDADE_FUNCIONAL_H

#include <stdbool.h>

typedef enum { ADD, MUL, INT } tipoUF;

typedef struct UF {
    tipoUF tipo;
    bool busy;
    unsigned int operacao;
    unsigned int fi;
    unsigned int fj;
    unsigned int fk;
    struct UF* qj;
    struct UF* qk;
    bool rj;
    bool rk;
    int qtde_ciclos;
} UF;

typedef struct {
    UF* ufAdd;
    UF* ufMul;
    UF* ufInt;
    int qtdeADD, qtdeMUL, qtdeINT;
} conjuntoUFS;

extern UF * vetorResultados; //Esse vetor serve para mostrar quais registradores de destino vão ser escritos ao final da execução 
extern conjuntoUFS unidadesFuncionais;

void printConjuntoUFS(conjuntoUFS* conjunto);
void printUF(UF* uf);
void inicializaConjuntoUFs(conjuntoUFS* UFS, int add, int mul, int inteiro);
int getUFdisponivel(UF* uf);
int ufDisponivel(tipoUF tipo, conjuntoUFS *UFS);
tipoUF getUF(unsigned int instrucao);

#endif // UNIDADEFUNCIONAL_H

