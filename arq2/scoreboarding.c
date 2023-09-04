#include <stdlib.h>
#include <stdio.h>
#include "scoreboarding.h"
#include "memoria.h"
#include "registradores.h"
#include "unidade_funcional.h"
#include <stdbool.h>

statusInstrucoes *statusI;
char* statusReg[32];

void inicializaStatusInstrucoes(){
    statusI = (statusInstrucoes*)malloc(sizeof(statusI)*qtdeInsts);
}

void statusRegistradores(){
    printf("\n-------------------------------------------- STATUS REGISTRADORES --------------------------------------------\n\n");
    for (int i = 0; i < 16; i++) {
        printf("R%d\t", i);
    }
    printf("\n");
    
    for (int i = 0; i < 16; i++) {
        printf("%s\t", statusReg[i]);
    }
    printf("\n\n");

    for (int i = 16; i < 32; i++) {
        printf("R%d\t", i);
    }
    printf("\n");
    
    for (int i = 16; i < 32; i++) {
        printf("%s\t", statusReg[i]);
    }
    printf("\n");
}

void statusUFs(){
    printf("\n\n| %-10s | %-10s | %-5s | %-10s | %-5s | %-5s | %-5s | %-10s | %-10s | %-5s | %-5s | %-15s |\n", "Nome","Tipo", "Busy", "Operacao", "Fi", "Fj", "Fk", "Qj", "Qk", "Rj", "Rk", "Quantidade Ciclos");
    
    for(int i=0; i<unidadesFuncionais.qtdeADD; i++){
        printf("\nNOME: %s", unidadesFuncionais.ufAdd[i].nome);
        printf("\nTIPO: %s", tipoToString(unidadesFuncionais.ufAdd[i].tipo));
        printf("\nBUSY: %d", unidadesFuncionais.ufAdd[i].busy);
        printf("\nOPERACAO: %d", unidadesFuncionais.ufAdd[i].operacao);
        printf("\nFI: %d", unidadesFuncionais.ufAdd[i].fi);
        printf("\nFJ: %d", unidadesFuncionais.ufAdd[i].fj);
        printf("\nFK: %d", unidadesFuncionais.ufAdd[i].fk);
        /* printf("\nQJ: %s", unidadesFuncionais.ufAdd[i].qj->nome);
        printf("\nQK: %s", unidadesFuncionais.ufAdd[i].qk->nome); */
        printf("\nRJ: %d", unidadesFuncionais.ufAdd[i].rj);
        printf("\nRK: %d", unidadesFuncionais.ufAdd[i].rk);
        printf("\nQTDE_CICLOS: %d", unidadesFuncionais.ufAdd[i].qtde_ciclos);

    } 
 

    
    /* for(int i=0; i<unidadesFuncionais.qtdeADD; i++){
        printf("|------------|-------|------------|-------|-------|-------|------------|------------|-------|-------|-----------------|\n");
        printf("| %-10s | %-10s | %-10d | %-5d | %-10u | %-5u | %-5u | %-5u | %-10s | %-10s | %-5d | %-5d | %-15d |\n",
        unidadesFuncionais.ufAdd[i].nome,
        tipoToString(unidadesFuncionais.ufAdd[i].tipo),
        unidadesFuncionais.ufAdd[i].tipo,
        unidadesFuncionais.ufAdd[i].busy,
        unidadesFuncionais.ufAdd[i].operacao,
        unidadesFuncionais.ufAdd[i].fi,
        unidadesFuncionais.ufAdd[i].fj,
        unidadesFuncionais.ufAdd[i].fk,
        unidadesFuncionais.ufAdd[i].qj->nome,
        unidadesFuncionais.ufAdd[i].qk->nome,
        unidadesFuncionais.ufAdd[i].rj,
        unidadesFuncionais.ufAdd[i].rk,
        unidadesFuncionais.ufAdd[i].qtde_ciclos);
    } */
    /* for(int i=0; i<unidadesFuncionais.qtdeMUL; i++){
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
    } */
}

void printStatusInstrucoes() {
    printf("\n\n%-20s%-14s%-14s%-14s%-14s%-14s\n\n", "Instrucao", "Busca", "Emissao", "Leitura_OP", "Execucao", "Escrita");
    for (int i = 0; i < qtdeInsts; i++) {
        printf("%-20d%-14d%-14d%-14d%-14d%-14d\n",
               statusI[i].instrucao, statusI[i].busca, statusI[i].emissao,
               statusI[i].leitura_op, statusI[i].execucao, statusI[i].escrita);
    }
}

























































