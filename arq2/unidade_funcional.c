#include <stdio.h>
#include <stdlib.h>
#include "unidade_funcional.h"
#include <stdbool.h>


const char* tipoToString(tipoUF tipo) {
    switch (tipo) {
        case ADD:
            return "ADD";
        case MUL:
            return "MUL";
        case INT:
            return "INT";
    }
}
/* 
void printConjuntoUFS(conjuntoUFS* conjunto) {
    printf("UF Add:\n");
    printUF(conjunto->ufAdd);
    
    printf("UF Mul:\n");
    printUF(conjunto->ufMul);
    
    printf("UF Int:\n");
    printUF(conjunto->ufInt);
} */


void printUFS(UF* ufs, int qtde){

    printf("UF  Tipo  Busy   Operacao   Fi      Fj      Fk       Qj       Qk     Rj     Rk\n");
    for (int i = 0; i < qtde; i++) {
        printf("%-4d %-4s %-7s %-7u %-7u %-7u %-7u %-6p %-6p %-6s %-7s\n",
               i, tipoToString(ufs[i].tipo), ufs[i].busy ? "true" : "false", ufs[i].operacao,
               ufs[i].fi, ufs[i].fj, ufs[i].fk, ufs[i].qj, ufs[i].qk,
               ufs[i].rj ? "true" : "false", ufs[i].rk ? "true" : "false");
    }
}


void inicializaConjuntoUFs(conjuntoUFS *UFS, int add, int mul, int inteiro){
    UFS->ufAdd = (UF*)malloc(sizeof(UF*)*add);
    UFS->ufMul = (UF*)malloc(sizeof(UF*)*mul);
    UFS->ufInt = (UF*)malloc(sizeof(UF*)*inteiro);
}

int getUFdisponivel(UF *uf){
    for(int i=0; i<sizeof(uf); i++){
        if(uf[i].busy == false){
            return i;
        }
    }
}

int ufDisponivel(tipoUF tipo, conjuntoUFS *UFS){
    if(tipo==ADD){
        for(int i=0; i<sizeof(UFS->ufAdd); i++){
            if(UFS->ufAdd->busy==1){
                return 0;
            }
        }
    }
    if(tipo==MUL){
        for(int i=0; i<sizeof(UFS->ufMul); i++){
            if(UFS->ufMul->busy==1){
                return 0;
            }
        }
    }
    if(tipo==INT){
        for(int i=0; i<sizeof(UFS->ufInt); i++){
            if(UFS->ufInt->busy==1){
                return 0;
            }
        }
    }

    return 1;
}

/* tipoUF getUF(unsigned int instrucao){
    if(getOpcode(instrucao)==0 || getOpcode(instrucao)==1 || getOpcode(instrucao)==2 || getOpcode(instrucao)==3){
        return ADD;
    }
    else if(getOpcode(instrucao)==4 || getOpcode(instrucao)==5){
        return MUL;
    }
    else if(getOpcode(instrucao)==6 || getOpcode(instrucao)==7 || getOpcode(instrucao)==8 || getOpcode(instrucao)==14 || getOpcode(instrucao)==15){
        return INT;
    }
} */
