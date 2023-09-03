#include <stdio.h>
#include <stdlib.h>
#include "unidade_funcional.h"
#include "processor.h"
#include "main.h"
#include <stdbool.h>

conjuntoUFS unidadesFuncionais;
UF *vetorResultados[32];

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


void inicializaUFs(int add, int mul, int inter){
    unidadesFuncionais.ufAdd = (UF*)malloc(sizeof(UF*)*add);
    unidadesFuncionais.ufInt = (UF*)malloc(sizeof(UF*)*inter);
    unidadesFuncionais.ufMul = (UF*)malloc(sizeof(UF*)*mul);
    unidadesFuncionais.qtdeADD = add;
    unidadesFuncionais.qtdeINT = inter;
    unidadesFuncionais.qtdeMUL = mul;
    for(int i=0; i<unidadesFuncionais.qtdeADD; i++){
        unidadesFuncionais.ufAdd[i].qtde_ciclos = -1;
    }
    for(int i=0; i<unidadesFuncionais.qtdeMUL; i++){
        unidadesFuncionais.ufMul[i].qtde_ciclos = -1;
    }
    for(int i=0; i<unidadesFuncionais.qtdeINT; i++){
        unidadesFuncionais.ufInt[i].qtde_ciclos = -1;
    }
}

/* int getUFdisponivel(UF *uf){
    for(int i=0; i<sizeof(uf); i++){
        if(uf[i].busy == false){
            return i;
        }
    }
} */

int getUFdisponivel(int tipo){
    if(tipo==0){
        for(int i=0; i<unidadesFuncionais.qtdeADD; i++){
            if(unidadesFuncionais.ufAdd[i].busy==0){
                return i;
            }
        }
    }
    if(tipo==1){
        for(int i=0; i<unidadesFuncionais.qtdeMUL; i++){
            if(unidadesFuncionais.ufAdd[i].busy==0){
                return i;
            }
        }
    }
    if(tipo==2){
        for(int i=0; i<unidadesFuncionais.qtdeINT; i++){
            if(unidadesFuncionais.ufAdd[i].busy==0){
                return i;
            }
        }
    }

    return -1;
}

int UFresultado(){

}

int getTipoUF(unsigned int instrucao){
    if(getOpcode(instrucao)==0 || getOpcode(instrucao)==1 || getOpcode(instrucao)==2 || getOpcode(instrucao)==3){
        return ADD;
    }
    else if(getOpcode(instrucao)==4 || getOpcode(instrucao)==5){
        return MUL;
    }
    else if(getOpcode(instrucao)==6 || getOpcode(instrucao)==7 || getOpcode(instrucao)==8 || getOpcode(instrucao)==14 || getOpcode(instrucao)==15){
        return INT;
    }
} 
