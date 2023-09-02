#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "processor.h"

pipeline pipe;

void inicializaPipeline(int add, int mul, int inteiro){

    pipe.execucao.ufAdd=(UF*)malloc(sizeof(UF*)*add);
    pipe.execucao.ufInt=(UF*)malloc(sizeof(UF*)*mul);
    pipe.execucao.ufMul=(UF*)malloc(sizeof(UF*)*inteiro);
    pipe.execucao.ufAdd->tipo=0;
    pipe.execucao.ufMul->tipo=1;
    pipe.execucao.ufInt->tipo=2;

}

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


int verificaWAW(pipeline pipe, conjuntoUFS *UFS){
    for(int i=0; i<3; i++){
        //AO INVÉS DE SIZEOF TEM QUE USAR O TAMANHO DA UF QUE FOI PASSADO COMO PARAMETRO
        for(int j=0; j<sizeof(UFS->ufAdd); j++){
            if(getRegistradorFonte1(pipe.busca)==UFS->ufAdd[j].fi){
                return 0;
            }
            if(getRegistradorFonte2(pipe.busca)==UFS->ufAdd[j].fi){
                return 0;
            }
        }
        for(int j=0; j<sizeof(UFS->ufMul); j++){
            if(getRegistradorFonte1(pipe.busca)==UFS->ufMul[j].fi){
                return 0;
            }
            if(getRegistradorFonte2(pipe.busca)==UFS->ufMul[j].fi){
                return 0;
            }
        }
        for(int j=0; j<sizeof(pipe.execucao.ufInt); j++){
            if(getRegistradorFonte1(pipe.busca)==UFS->ufInt[j].fi){
                return 0;
            }
            if(getRegistradorFonte2(pipe.busca)==UFS->ufInt[j].fi){
                return 0;
            }
        }
    }
    //NAO PRECISA VERIFICAR TUDO ISSO EH SO OLHAR NA UF EU ACHO
    /*
    if(getRegistradorFonte1(pipe.busca)==getRegistradorDestino(pipe.leitura_op)){
        return 0;
    }
    if(getRegistradorFonte2(pipe.busca)==getRegistradorDestino(pipe.leitura_op)){
        return 0;
    }
    if(getRegistradorFonte1(pipe.busca)==getRegistradorDestino(pipe.escrita)){
        return 0;
    }
    if(getRegistradorFonte2(pipe.busca)==getRegistradorDestino(pipe.escrita)){
        return 0;
    }
    if(getRegistradorFonte1(pipe.busca)==getRegistradorDestino(pipe.emissao)){
        return 0;
    }
    if(getRegistradorFonte2(pipe.busca)==getRegistradorDestino(pipe.emissao)){
        return 0;
    }
    */
    return 1;
}

/* void emiteInstrucao(pipeline *pipe, conjuntoUFS *UFS){
    if(verificaWAW(*pipe, UFS) && ufDisponivel(getUF(pipe->busca), UFS)){
        tipoUF ufinst = getUF(pipe->busca);
        if(ufinst==ADD){
            int disponivel = getUFdisponivel(UFS->ufAdd);
            UFS->ufAdd[disponivel].busy = 1;
            UFS->ufAdd[disponivel].fi = getRegistradorDestino(pipe->busca);
            UFS->ufAdd[disponivel].fj = getValor(getRegistradorFonte1(pipe->busca));
            UFS->ufAdd[disponivel].fk = getValor(getRegistradorFonte2(pipe->busca));
            UFS->ufAdd[disponivel].operacao = getOpcode(pipe->busca);
            UFS->ufAdd[disponivel].qj = UFresultado(getRegistradorFonte1(pipe->busca));
            UFS->ufAdd[disponivel].qk = UFresultado(getRegistradorFonte2(pipe->busca));
            //ACHO QUE NAO PRECISA DE TUDO ISSOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO
            /*
            for(int i=0; i<sizeof(UFS->ufAdd); i++){
                if(UFS->ufAdd[i].busy==0){
                    UFS->ufAdd[i].busy = 1;
                    //VERIFICAR SE O VALOR A SER ESCRITO JÁ ESTÁ PRONTO
                    //PRA FAZER ISSO BASTA VERIFICAR SE O REGISTRADOR É DESTINO DE ALGUMA OPERACAO NAS UFS
                    //AO INVÉS DE SIZEOF TEM QUE USAR O TAMANHO DA UF QUE FOI PASSADO COMO PARAMETRO
                    //PROBLEMA AQUI::: SABER QUAL FOI O ÚLTIMO A ENTRAR NO PIPELINE
                    for(int j=0; j<sizeof(UFS->ufAdd); j++){
                        if(UFS->ufAdd[j].fi==getRegistradorFonte1(pipe->busca)){
                            UFS->ufAdd[i].qj = j;
                        }
                        if( UFS->ufAdd[j].fi==getRegistradorFonte2(pipe->busca)){
                            UFS->ufAdd[i].qk = j;
                        }

                    }
                    for(int j=0; j<sizeof(UFS->ufMul); j++){
                        if(UFS->ufMul[j].fi==getRegistradorFonte1(pipe->busca)){
                            UFS->ufMul[i].qj = j;
                        }
                        if( UFS->ufMul[j].fi==getRegistradorFonte2(pipe->busca)){
                            UFS->ufMul[i].qk = j;
                        }
                    }
                    for(int j=0; j<sizeof(UFS->ufInt); j++){
                        if(UFS->ufInt[j].fi==getRegistradorFonte1(pipe->busca)){
                            UFS->ufInt[i].qj = j;
                        }
                        if( UFS->ufInt[j].fi==getRegistradorFonte2(pipe->busca)){
                            UFS->ufInt[i].qk = j;
                        }
                    }
                    //UFS->ufAdd[i].fi = getRegistradorDestino(pipe->busca);
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