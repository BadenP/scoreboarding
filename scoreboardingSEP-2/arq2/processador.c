#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "processador.h"

typedef struct {
    unsigned int busca;
    unsigned int emissao;
    unsigned int leitura_op;
    conjuntoUFS execucao;
    unsigned int escrita;
}pipeline;


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

tipoUF getUF(unsigned int instrucao){
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

int ufDisponivel(pipeline *pipe, tipoUF tipo, conjuntoUFS *UFS){
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

int getUFdisponivel(UF *uf){
    for(int i=0; i<sizeof(uf); i++){
        if(uf[i].busy == 0){
            return i;
        }
    }
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

/* int UFresultado(int registrador){
    for(int i=0; i<)
} */

void emiteInstrucao(pipeline *pipe, conjuntoUFS *UFS){
    if(verificaWAW(*pipe, UFS) && ufDisponivel(pipe, getUF(pipe->busca), UFS)){
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
            }*/
        }
        pipe->emissao = pipe->busca;
        pipe->busca = 0;
    }
    else{
        //STALL
    }
}

void leituraOperandos(pipeline *pipe){
    pipe->leitura_op = pipe->emissao;
    pipe->emissao = 0;
}

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
}


/* 
int main(int argc, char *argv[]){

    int m=11;
    int qtdeAdd = 2;
    int qtdeMul = 3;
    int qtdeInt = 1;
    unsigned int exemploPrograma[10]={50,100,150,200,250,300,350,400,450,500};
    unsigned int barramento = 0;
    conjuntoUFS UFS;
    //leitura do programa FEITO

    //fase de inicializacao FEITA
    /* A memória tem que ser inicializada
        As UFS tem que ser inicializadas
        Banco de registradores
        Pipeline
    
    */
    //Tem que inicializar o banco com os dados obtidos em .dados
    //inicializaPipeline(qtdeAdd,qtdeMul,qtdeInt);
    //inicializaMemoria(m);
    //inicializaConjuntoUFs(&UFS, qtdeAdd, qtdeMul, qtdeInt);
    //printUFS(pipe->execucao,8);
    //imprimeMemoria(m);

    //carrega o programa para a memoria
    /* for (int i=0; i<sizeof(exemploPrograma)/sizeof(exemploPrograma[0]); i++){
        insereMemoria(exemploPrograma[i], i);
    } */

    printMemoria();
    int clock = 0;
    //começa a execução do pipeline
     //while(getOpcode(pipe.busca)!=16){
        //if(pipe.escrita!=0){
            //ESCREVER NO REGISTRADOR
            //exemplo reg[indice]=?
            //pipe.escrita=0;
        //}
    pipe.busca = buscaInstrucao(pipe, pc, barramento);
    printf("\n\n%u\n\n", pipe.busca);
    emiteInstrucao(&pipe, &UFS);
        //Para cada UF, verificar se UF.qtde_ciclos==0 AND não tem WAR
        //Se já terminou e não tem WAR, pipe.escrita=instrucao q ta na UF
        //Se não terminou faz UF.qtde_ciclos-1 
        //Tem muita coisa pra fazer nessa parte pqp 

        /*if(pipe.leitura_op){


        
        }

        if(1/*se tem UF livre){
            pipe.leitura_op=0;
            //enfia na execucao
        }
        else{
            //deixa a instrucao lá, ou seja, pipe.leitura_op!=0
        }

        if(1/*pipe.leitura_op==0 AND //verifica war){

            //manda p pipe.leitura_op
        }pc++;
        else{
            //continua do jeito q ta 
        }

        /*
        if(WAW){
            //nao emite
            //nao busca a proxima
        }
        else{
            //emite
            //busca a proxima
            pipe.busca=memoria[pc];
        }*/
        
        pc++;
        clock++;

    //} 




    //fim
    free(memoria);





}
 */