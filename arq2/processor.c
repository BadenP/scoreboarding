#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "processor.h"

pipeline pipe;

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



void emiteInstrucao(){
    int regDestino = getRegistradorDestino(pipe.busca);
    tipoUF tipoUF_inst = getTipoUF(pipe.busca);
    int disponivel = getUFDisponivel(tipoUF_inst);
    if(regDestino!=vetorResultados[regDestino].fi && disponivel!=-1){
        if(tipoUF_inst==ADD){
            unidadesFuncionais.ufAdd[disponivel].busy = true;
            unidadesFuncionais.ufAdd[disponivel].fi = getRegistradorDestino(pipe.busca);
            unidadesFuncionais.ufAdd[disponivel].fj = getValor(getRegistradorFonte1(pipe.busca));
            unidadesFuncionais.ufAdd[disponivel].fk = getValor(getRegistradorFonte2(pipe.busca));
            unidadesFuncionais.ufAdd[disponivel].operacao = getOpcode(pipe.busca);
            unidadesFuncionais.ufAdd[disponivel].qj = UFresultado(getRegistradorFonte1(pipe.busca));
            unidadesFuncionais.ufAdd[disponivel].qk = UFresultado(getRegistradorFonte2(pipe.busca));

            pipe.emissao=pipe.busca;
            //ACHO QUE NAO PRECISA DE TUDO ISSOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO
            /*
            for(int i=0; i<sizeof(unidadesFuncionais->ufAdd); i++){
                if(unidadesFuncionais->ufAdd[i].busy==0){
                    unidadesFuncionais->ufAdd[i].busy = 1;
                    //VERIFICAR SE O VALOR A SER ESCRITO JÁ ESTÁ PRONTO
                    //PRA FAZER ISSO BASTA VERIFICAR SE O REGISTRADOR É DESTINO DE ALGUMA OPERACAO NAS unidadesFuncionais
                    //AO INVÉS DE SIZEOF TEM QUE USAR O TAMANHO DA UF QUE FOI PASSADO COMO PARAMETRO
                    //PROBLEMA AQUI::: SABER QUAL FOI O ÚLTIMO A ENTRAR NO PIPELINE
                    for(int j=0; j<sizeof(unidadesFuncionais->ufAdd); j++){
                        if(unidadesFuncionais->ufAdd[j].fi==getRegistradorFonte1(pipe->busca)){
                            unidadesFuncionais->ufAdd[i].qj = j;
                        }
                        if( unidadesFuncionais->ufAdd[j].fi==getRegistradorFonte2(pipe->busca)){
                            unidadesFuncionais->ufAdd[i].qk = j;
                        }

                    }
                    for(int j=0; j<sizeof(unidadesFuncionais->ufMul); j++){
                        if(unidadesFuncionais->ufMul[j].fi==getRegistradorFonte1(pipe->busca)){
                            unidadesFuncionais->ufMul[i].qj = j;
                        }
                        if( unidadesFuncionais->ufMul[j].fi==getRegistradorFonte2(pipe->busca)){
                            unidadesFuncionais->ufMul[i].qk = j;
                        }
                    }
                    for(int j=0; j<sizeof(unidadesFuncionais->ufInt); j++){
                        if(unidadesFuncionais->ufInt[j].fi==getRegistradorFonte1(pipe->busca)){
                            unidadesFuncionais->ufInt[i].qj = j;
                        }
                        if( unidadesFuncionais->ufInt[j].fi==getRegistradorFonte2(pipe->busca)){
                            unidadesFuncionais->ufInt[i].qk = j;
                        }
                    }
                    //unidadesFuncionais->ufAdd[i].fi = getRegistradorDestino(pipe->busca);
                }
            
        }
        pipe->emissao = pipe->busca;
        pipe->busca = 0;
    }
    else{
        //STALL
    }
} */

void leituraOperandos(pipeline *pipe){
    pipe->leitura_op = pipe->emissao;
    pipe->emissao = 0;
}
/* 
void executaInstrucao(pipeline *pipe){
    tipoUF ufinst = getUF(pipe->leitura_op);
    //PRECISA PROCURAR NA UF ESPAÇO VAZIO
    if(ufinst==ADD){
        //AO INVÉS DE SIZEOF TEM QUE USAR O TAMANHO DA UF QUE FOI PASSADO COMO PARAMETRO
        for(int i=0; i<sizeof(pipe->execucao.ufAdd); i++){
            if(pipe->execucao.ufAdd[i].busy == 0){
                //pipe->execucao.ufAdd[i].
                return;
            }
        }
    }
} */