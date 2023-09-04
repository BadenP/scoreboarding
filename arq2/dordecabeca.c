#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "processor.h"

int buscaInstrucao(pipeline pipe, int pc, int barramento){
    colocaBarramento(memoria[pc]);
    pipe.busca = pegaBarramento(barramento);
    return pipe.busca;
}

unsigned int getOpcode(unsigned int instrucao){
    unsigned int codOpcode = (instrucao >> 26) & 0x3F;
    return codOpcode;
} 

unsigned int getRegistradorDestino(unsigned int instrucao){
    unsigned int destino;
    if(getOpcode(instrucao)==0 || getOpcode(instrucao)==2 || getOpcode(instrucao)==4 || getOpcode(instrucao)==5 || getOpcode(instrucao)==6 || getOpcode(instrucao)==7 || getOpcode(instrucao)==8){
        destino = (instrucao >> 11) & 0x1F;
    }
    else if(getOpcode(instrucao)==1 || getOpcode(instrucao)==3 || getOpcode(instrucao)==14){
        destino = (instrucao >> 16) & 0x1F;
    }
    return destino;    
} 

unsigned int getRegistradorFonte1(unsigned int instrucao){
    unsigned int fonte1;
    if(getOpcode(instrucao)!=13 && getOpcode(instrucao)!=15 && getOpcode(instrucao)!=16)
        fonte1 = (instrucao >> 21) & 0x1F;
    return fonte1;    
} 

unsigned int getRegistradorFonte2(unsigned int instrucao){
    unsigned int fonte2;
    if(getOpcode(instrucao)!=1 && getOpcode(instrucao)!=3 && getOpcode(instrucao)!=8 && getOpcode(instrucao)!=13 && getOpcode(instrucao)!=14)
        fonte2 = (instrucao >> 16) & 0x1F;
    return fonte2;    
}

int clock=0;
int pc=0;

int busca(){
    //desgraça de barramento
    //escreve o ciclo de clock na bosta do status UF 
    statusI.busca=clock;
    return memoria[pc];
}

int emite(){
    statusI.emissao=clock;
    //MUDA A UF DO CARALHO
    return memoria[pc];
}


int main(){

    while(getOpcode(busca())!=16){

        busca();
        emite();
        le_operandos();
        executa();
        escreve();

    }










}

