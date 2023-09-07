#include <stdlib.h>
#include <stdio.h>
#include "scoreboarding.h"
#include "memoria.h"
#include "registradores.h"
#include "unidade_funcional.h"

statusInstrucoes *statusI;


void inicializaStatusInstrucoes(){
    statusI = (statusInstrucoes*)malloc(sizeof(statusInstrucoes)*qtdeInsts);
    int j=0;
    int i=100;
    while(memoria[i]!=0){
        printf("entrou %d\n",i);
        statusI[j].instrucao = memoria[i];
        j++;
        i=i+4;
    } 
}


void statusRegistradores(){
    for(int i=0; i<32; i++){
        printf("\nr%d = %d", i, bancoRegs[i]);
    }
}


int getIndiceInstrucao(int instrucao){

    for (int i=0; i<qtdeInsts; i++){
        if(statusI[i].instrucao==instrucao){
            return i;
        }
    }
}



void printStatusInstrucoes() {
    printf("\n\n%-20s%-14s%-14s%-14s%-14s%-14s\n\n", "Instrucao", "Busca", "Emissao", "Leitura_OP", "Execucao", "Escrita");
    for (int i = 0; i < qtdeInsts; i++) {
        printf("%-20d%-14d%-14d%-14d%-14d%-14d\n",
               statusI[i].instrucao, statusI[i].busca, statusI[i].emissao,
               statusI[i].leitura_op, statusI[i].execucao, statusI[i].escrita);
    }
}

void statusUFs(){
    printf("| %-10s | %-5s | %-10s | %-5s | %-5s | %-5s | %-10p | %-10p | %-5s | %-5s | %-15s |\n", "Tipo", "Busy", "Operacao", "Fi", "Fj", "Fk", "Qj", "Qk", "Rj", "Rk", "Quantidade Ciclos");
    for(int i=0; i<unidadesFuncionais.qtdeADD; i++){
        printf("|------------|-------|------------|-------|-------|-------|------------|------------|-------|-------|-----------------|\n");
        printf("| %-10d | %-5d | %-10u | %-5u | %-5u | %-5u | %-10p | %-10p | %-5d | %-5d | %-15d |\n",
        unidadesFuncionais.ufAdd[i].tipo,
        unidadesFuncionais.ufAdd[i].busy,
        unidadesFuncionais.ufAdd[i].operacao,
        unidadesFuncionais.ufAdd[i].fi,
        unidadesFuncionais.ufAdd[i].fj,
        unidadesFuncionais.ufAdd[i].fk,
        (void *)unidadesFuncionais.ufAdd[i].qj,
        (void *)unidadesFuncionais.ufAdd[i].qk,
        unidadesFuncionais.ufAdd[i].rj,
        unidadesFuncionais.ufAdd[i].rk,
        unidadesFuncionais.ufAdd[i].qtde_ciclos);
    }
    for(int i=0; i<unidadesFuncionais.qtdeMUL; i++){
        printf("|------------|-------|------------|-------|-------|-------|------------|------------|-------|-------|-----------------|\n");
        printf("| %-10d | %-5d | %-10u | %-5u | %-5u | %-5u | %-10p | %-10p | %-5d | %-5d | %-15d |\n",
        unidadesFuncionais.ufMul[i].tipo,
        unidadesFuncionais.ufMul[i].busy,
        unidadesFuncionais.ufMul[i].operacao,
        unidadesFuncionais.ufMul[i].fi,
        unidadesFuncionais.ufMul[i].fj,
        unidadesFuncionais.ufMul[i].fk,
        (void *)unidadesFuncionais.ufMul[i].qj,
        (void *)unidadesFuncionais.ufMul[i].qk,
        unidadesFuncionais.ufMul[i].rj,
        unidadesFuncionais.ufMul[i].rk,
        unidadesFuncionais.ufMul[i].qtde_ciclos);
    }
    for(int i=0; i<unidadesFuncionais.qtdeINT; i++){
        printf("|------------|-------|------------|-------|-------|-------|------------|------------|-------|-------|-----------------|\n");
        printf("| %-10d | %-5d | %-10u | %-5u | %-5u | %-5u | %-10p | %-10p | %-5d | %-5d | %-15d |\n",
        unidadesFuncionais.ufInt[i].tipo,
        unidadesFuncionais.ufInt[i].busy,
        unidadesFuncionais.ufInt[i].operacao,
        unidadesFuncionais.ufInt[i].fi,
        unidadesFuncionais.ufInt[i].fj,
        unidadesFuncionais.ufInt[i].fk,
        (void *)unidadesFuncionais.ufInt[i].qj,
        (void *)unidadesFuncionais.ufInt[i].qk,
        unidadesFuncionais.ufInt[i].rj,
        unidadesFuncionais.ufInt[i].rk,
        unidadesFuncionais.ufInt[i].qtde_ciclos);
    }
}






























