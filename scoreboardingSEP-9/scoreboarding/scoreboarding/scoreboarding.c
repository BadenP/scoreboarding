#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "scoreboarding.h"
#include "memoria.h"
#include "tradutor.h"
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
        if(statusI[i].instrucao==instrucao && statusI[i].escrita==0){
            return i;
        }
    }
}

int encontraQ(UF* unidadefuncional){
    for(int i=0; i<unidadesFuncionais.qtdeADD; i++){
        if(&unidadesFuncionais.ufAdd[i] == unidadefuncional){
            return i;
        }
    }
    for(int i=0; i<unidadesFuncionais.qtdeMUL; i++){
        if(&unidadesFuncionais.ufMul[i] == unidadefuncional){
            return i;
        }
    }
    for(int i=0; i<unidadesFuncionais.qtdeINT; i++){
        if(&unidadesFuncionais.ufInt[i] == unidadefuncional){
            return i;
        }
    }
    return 0;
}

void printStatusInstrucoes() {
    printf("\n\n%-25s%-14s%-14s%-14s%-14s%-14s\n\n", "Instrucao", "Busca", "Emissao", "Leitura_OP", "Execucao", "Escrita");
    for (int i = 0; i < qtdeInsts; i++) {
        printf("%-25s%-14d%-14d%-14d%-d--%-11d%-16d\n",
               instrucaoToString(statusI[i].instrucao), statusI[i].busca, statusI[i].emissao,
               statusI[i].leitura_op, statusI[i].execucaoinicio, statusI[i].execucaofim, statusI[i].escrita);
    }
}

void statusUFs(){
    printf("\n| %-10s | %-5s | %-10s | %-5s | %-5s | %-5s | %-10s | %-10s | %-5s | %-5s | %-15s |\n", "Tipo", "Busy", "Operacao", "Fi", "Fj", "Fk", "Qj", "Qk", "Rj", "Rk", "Quantidade Ciclos");
    for(int i=0; i<unidadesFuncionais.qtdeADD; i++){
        printf("|------------|-------|------------|-------|-------|-------|------------|------------|-------|-------|-------------------|\n");
        //char *nome_qj = encontrarNomeObjeto(unidadesFuncionais.ufAdd[i].qj);
        //char *nome_qk = encontrarNomeObjeto(unidadesFuncionais.ufAdd[i].qk);
        char* qj;
        if(unidadesFuncionais.ufAdd[i].qj!=0){
            if(unidadesFuncionais.ufAdd[i].qj->tipo==0){
                qj = "ADD";
            }
            else if(unidadesFuncionais.ufAdd[i].qj->tipo==1){
                qj = "MUL";
            }
            else if(unidadesFuncionais.ufAdd[i].qj->tipo==2){
                qj = "INT";
            }
        }
        else{
            qj = "-";
        }
        char* qk;
        if(unidadesFuncionais.ufAdd[i].qk!=0){
            if(unidadesFuncionais.ufAdd[i].qk->tipo==0){
                qk = "ADD";
            }
            else if(unidadesFuncionais.ufAdd[i].qk->tipo==1){
                qk = "MUL";
            }
            else if(unidadesFuncionais.ufAdd[i].qk->tipo==2){
                qk = "INT";
            }
        }
        else{
            qk = "-";
        }
        printf("| %-10s | %-5d | %-10u | %-5u | %-5u | %-5u | %-5s%-5d | %-5s%-5d | %-5d | %-5d | %-17d |\n",
        "ADD",
        unidadesFuncionais.ufAdd[i].busy,
        unidadesFuncionais.ufAdd[i].operacao,
        unidadesFuncionais.ufAdd[i].fi,
        unidadesFuncionais.ufAdd[i].fj,
        unidadesFuncionais.ufAdd[i].fk,
        qj, encontraQ(unidadesFuncionais.ufAdd[i].qj),
        qk, encontraQ(unidadesFuncionais.ufAdd[i].qk),
        unidadesFuncionais.ufAdd[i].rj,
        unidadesFuncionais.ufAdd[i].rk,
        unidadesFuncionais.ufAdd[i].qtde_ciclos);
    }
    for(int i=0; i<unidadesFuncionais.qtdeMUL; i++){
        printf("|------------|-------|------------|-------|-------|-------|------------|------------|-------|-------|-------------------|\n");
        char* qj;
        if(unidadesFuncionais.ufMul[i].qj!=0){
            if(unidadesFuncionais.ufMul[i].qj->tipo==0){
                qj = "ADD";
            }
            else if(unidadesFuncionais.ufMul[i].qj->tipo==1){
                qj = "MUL";
            }
            else if(unidadesFuncionais.ufMul[i].qj->tipo==2){
                qj = "INT";
            }
        }
        else{
            qj = "-";
        }
        char* qk;
        if(unidadesFuncionais.ufMul[i].qk!=0){
            if(unidadesFuncionais.ufMul[i].qk->tipo==0){
                qk = "ADD";
            }
            else if(unidadesFuncionais.ufMul[i].qk->tipo==1){
                qk = "MUL";
            }
            else if(unidadesFuncionais.ufMul[i].qk->tipo==2){
                qk = "INT";
            }
        }
        else{
            qk = "-";
        }
        printf("| %-10s | %-5d | %-10u | %-5u | %-5u | %-5u | %-5s%-5d | %-5s%-5d | %-5d | %-5d | %-17d |\n",
        "MUL",
        unidadesFuncionais.ufMul[i].busy,
        unidadesFuncionais.ufMul[i].operacao,
        unidadesFuncionais.ufMul[i].fi,
        unidadesFuncionais.ufMul[i].fj,
        unidadesFuncionais.ufMul[i].fk,
        qj, encontraQ(unidadesFuncionais.ufMul[i].qj),
        qk, encontraQ(unidadesFuncionais.ufMul[i].qk),
        unidadesFuncionais.ufMul[i].rj,
        unidadesFuncionais.ufMul[i].rk,
        unidadesFuncionais.ufMul[i].qtde_ciclos);
    }
    for(int i=0; i<unidadesFuncionais.qtdeINT; i++){
        printf("|------------|-------|------------|-------|-------|-------|------------|------------|-------|-------|-------------------|\n");
        char* qj;
        if(unidadesFuncionais.ufInt[i].qj!=0){
            if(unidadesFuncionais.ufInt[i].qj->tipo==0){
                qj = "ADD";
            }
            else if(unidadesFuncionais.ufInt[i].qj->tipo==1){
                qj = "MUL";
            }
            else if(unidadesFuncionais.ufInt[i].qj->tipo==2){
                qj = "INT";
            }
        }
        else{
            qj = "-";
        }
        char* qk;
        if(unidadesFuncionais.ufInt[i].qk!=0){
            if(unidadesFuncionais.ufInt[i].qk->tipo==0){
                qk = "ADD";
            }
            else if(unidadesFuncionais.ufInt[i].qk->tipo==1){
                qk = "MUL";
            }
            else if(unidadesFuncionais.ufInt[i].qk->tipo==2){
                qk = "INT";
            }
        }
        else{
            qk = "-";
        }
        printf("| %-10s | %-5d | %-10u | %-5u | %-5u | %-5u | %-5s%-5d | %-5s%-5d | %-5d | %-5d | %-17d |\n",
        "INT",
        unidadesFuncionais.ufInt[i].busy,
        unidadesFuncionais.ufInt[i].operacao,
        unidadesFuncionais.ufInt[i].fi,
        unidadesFuncionais.ufInt[i].fj,
        unidadesFuncionais.ufInt[i].fk,
        qj, encontraQ(unidadesFuncionais.ufInt[i].qj),
        qk, encontraQ(unidadesFuncionais.ufInt[i].qk),
        unidadesFuncionais.ufInt[i].rj,
        unidadesFuncionais.ufInt[i].rk,
        unidadesFuncionais.ufInt[i].qtde_ciclos);
    }
}






























