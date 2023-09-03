#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "processor.h"
#include "registradores.h"
#include "unidade_funcional.h"
#include "scoreboarding.h"
#include "main.h"

void buscaInstrucao(){
    colocaBarramento(memoria[pc]);
    ir = pegaBarramento();
    statusI[pc].busca = clock;
    printf("\n%d", ir);
}

unsigned int getOpcode(unsigned int instrucao){
    unsigned int codOpcode = (instrucao >> 26) & 0x3F;
    return codOpcode;
} 

//PARA AS INSTRUCOES DE LOAD E STORE:::: RT É DESTINO, IMM É FONTE1 E R2 É FONTE2

//PARA INSTRUÇÕES DE SALTO O DESTINO FOI UTILIZADO PARA ARMAZENAR O IMM
unsigned int getRegistradorDestino(unsigned int instrucao){
    unsigned int destino;
    if(getOpcode(instrucao)==0 || getOpcode(instrucao)==2 || getOpcode(instrucao)==4 || getOpcode(instrucao)==5 || getOpcode(instrucao)==6 || getOpcode(instrucao)==7 || getOpcode(instrucao)==8){
        destino = (instrucao >> 11) & 0x1F;
    }
    else if(getOpcode(instrucao)==1 || getOpcode(instrucao)==3 || getOpcode(instrucao)==14 || getOpcode(instrucao)==15){
        destino = (instrucao >> 16) & 0x1F;
    }
    else if(getOpcode(instrucao)==9 || getOpcode(instrucao)==10 || getOpcode(instrucao)==11 || getOpcode(instrucao)==12 || getOpcode(instrucao)==13){
        destino = (instrucao >> 16) & 0x1F;
    }
    return destino;    
} 

unsigned int getRegistradorFonte1(unsigned int instrucao){
    unsigned int fonte1;
    if(getOpcode(instrucao)!=13 && getOpcode(instrucao)!=14 && getOpcode(instrucao)!=15 && getOpcode(instrucao)!=16)
        fonte1 = (instrucao >> 21) & 0x1F;
    else if(getOpcode(instrucao)==14 || getOpcode(instrucao)==15){
        fonte1 = instrucao & 0xFFFF;
    }
    return fonte1;    
} 

unsigned int getRegistradorFonte2(unsigned int instrucao){
    unsigned int fonte2;
    if(getOpcode(instrucao)!=1 && getOpcode(instrucao)!=3 && getOpcode(instrucao)!=8 && getOpcode(instrucao)!=13 && getOpcode(instrucao)!=14 && getOpcode(instrucao)!=15)
        fonte2 = (instrucao >> 16) & 0x1F;
    else if(getOpcode(instrucao)==14 || getOpcode(instrucao)==15){
        fonte2 = (instrucao >> 21) && 0x1F;
    }
    return fonte2;    
}


//SÓ PRA RETORNAR A QUANTIDADE DE CICLOS QUE A INSTRUCAO VAI LEVAR PRA EXECUTAR
int getCiclos(int opcode){
    if(opcode==0){
        return addCiclos;
    }
    else if(opcode==1){
        return addiCiclos;
    }
    else if(opcode==2){
        return subCiclos;
    }
    else if(opcode==3){
        return subiCiclos;
    }
    else if(opcode==4){
        return mulCiclos;
    }
    else if(opcode==5){
        return divCiclos;
    }
    else if(opcode==6){
        return andCiclos;
    }
    else if(opcode==7){
        return orCiclos;
    }
    else if(opcode==8){
        return notCiclos;
    }
    else if(opcode==9){
        return bltCiclos;
    }
    else if(opcode==10){
        return bgtCiclos;
    }
    else if(opcode==11){
        return beqCiclos;
    }
    else if(opcode==12){
        return bneCiclos;
    }
    else if(opcode==13){
        return jCiclos;
    }
    else if(opcode==14){
        return lwCiclos;
    }
    else if(opcode==15){
        return swCiclos;
    }
}

//EXECUTA DE FATO AS OPERACOESSSSSSSS

//PROVAVEL QUE TENHA QUE ARREDONDAR OS VALORES QUANDO É DIV OU MUL PQ O ANDERSON DISSE QUE NAO VAMOS TRABALHAR COM FLOAT

//NAO SEI SE A OPERACAO NOT SÓ ALTERA O SINAL DO NUMERO OU DA TIPO UM COMPLEMENTO (???) DELE

//NOS SALTOS RS E RT SÃO FONTE1 E FONTE2 RESPECTIVAMENTE MAS AINDA PRECISO RESOLVER O IMM
//PQ NAO SEI ONDE ARMAZENO (PROVAVELMENTE NO DESTINO)
void executaInstrucao(int destino, int fonte1, int fonte2, int opcode){
    if(opcode==0){
        bancoRegs[destino] = bancoRegs[fonte1] + bancoRegs[fonte2];
    }
    else if(opcode==1){
        bancoRegs[destino] = bancoRegs[fonte1] + fonte2;
    }
    else if(opcode==2){
        bancoRegs[destino] = bancoRegs[fonte1] - bancoRegs[fonte2];
    }
    else if(opcode==3){
        bancoRegs[destino] = bancoRegs[fonte1] - fonte2;
    }
    else if(opcode==4){
        bancoRegs[destino] = bancoRegs[fonte1] * bancoRegs[fonte2];
    }
    else if(opcode==5){
        bancoRegs[destino] = bancoRegs[fonte1] / bancoRegs[fonte2];
    }
    else if(opcode==6){
        bancoRegs[destino] = bancoRegs[fonte1] & bancoRegs[fonte2];
    }
    else if(opcode==7){
        bancoRegs[destino] = bancoRegs[fonte1] | bancoRegs[fonte2];
    }
    else if(opcode==8){
        bancoRegs[destino] = -1 * bancoRegs[fonte1];
    }
    else if(opcode==9){
        if(bancoRegs[fonte1]<bancoRegs[fonte2]){
            pc = pc + 4 + destino;
        }
    }
    else if(opcode==10){
        if(bancoRegs[fonte1]>bancoRegs[fonte2]){
            pc = pc + 4 + destino;
        }
    }
    else if(opcode==11){
        if(bancoRegs[fonte1]==bancoRegs[fonte2]){
            pc = pc + 4 + destino;
        }
    }
    else if(opcode==12){
        if(bancoRegs[fonte1]!=bancoRegs[fonte2]){
            pc = pc + 4 + destino;
        }
    }
    //SALTO INCONDICIONAL (OPCODE 13) TEM QUE SER VISTO NA BUSCAAAAAAAAAA
    else if(opcode==14){
        bancoRegs[destino] = memoria[bancoRegs[fonte1] + fonte2];
    }
    else if(opcode==15){
        memoria[bancoRegs[fonte1] + fonte2] = bancoRegs[destino];
    }
}



//DEPOIS DE JOGAR AS INSTRUCOES PRA UF EU COLOCO OS DADOS E FAÇO A QUANTIDADE DE CICLOS = -1 
//PRA SINALIZAR QUE A LEITURA DE OPERANDOS AINDA NAO FOI FEITA E A EXECUCAO AINDA NAO PODE COMECAR

//DUVIDAS:::: DEPOIS DOS RESULTADOS ESTAREM PRONTOS QJ E QK ANULA?; NAO SEI DIREITO AINDA COMO VAI FUNCIONAR O VETORRESULTADOS
void emiteInstrucao(){
    int regDestino = getRegistradorDestino(ir);
    int tipoUF_inst = getTipoUF(ir);
    int disponivel = getUFdisponivel(tipoUF_inst);
    if(vetorResultados[regDestino] == 0 && disponivel!=-1){
        if(tipoUF_inst==ADD){
            unidadesFuncionais.ufAdd[disponivel].busy = 1;
            unidadesFuncionais.ufAdd[disponivel].fi = bancoRegs[regDestino];
            unidadesFuncionais.ufAdd[disponivel].fj = bancoRegs[getRegistradorFonte1(ir)];
            unidadesFuncionais.ufAdd[disponivel].fk = bancoRegs[getRegistradorFonte2(ir)];
            unidadesFuncionais.ufAdd[disponivel].operacao = getOpcode(ir);
            unidadesFuncionais.ufAdd[disponivel].qj = vetorResultados[getRegistradorFonte1(ir)];
            unidadesFuncionais.ufAdd[disponivel].qk = vetorResultados[getRegistradorFonte2(ir)];
            unidadesFuncionais.ufAdd[disponivel].rj = (unidadesFuncionais.ufAdd[disponivel].qj == 0);
            unidadesFuncionais.ufAdd[disponivel].rk = (unidadesFuncionais.ufAdd[disponivel].qk == 0);
            unidadesFuncionais.ufAdd[disponivel].qtde_ciclos = -1;
            vetorResultados[regDestino] = &unidadesFuncionais.ufAdd[disponivel];
        }
        if(tipoUF_inst==MUL){
            unidadesFuncionais.ufMul[disponivel].busy = 1;
            unidadesFuncionais.ufMul[disponivel].fi = bancoRegs[regDestino];
            unidadesFuncionais.ufMul[disponivel].fj = bancoRegs[getRegistradorFonte1(ir)];
            unidadesFuncionais.ufMul[disponivel].fk = bancoRegs[getRegistradorFonte2(ir)];
            unidadesFuncionais.ufMul[disponivel].operacao = getOpcode(ir);
            unidadesFuncionais.ufMul[disponivel].qj = vetorResultados[getRegistradorFonte1(ir)];
            unidadesFuncionais.ufMul[disponivel].qk = vetorResultados[getRegistradorFonte2(ir)];
            unidadesFuncionais.ufMul[disponivel].rj = (unidadesFuncionais.ufMul[disponivel].qj == 0);
            unidadesFuncionais.ufMul[disponivel].rk = (unidadesFuncionais.ufMul[disponivel].qk == 0);
            unidadesFuncionais.ufMul[disponivel].qtde_ciclos = -1;
            vetorResultados[regDestino] = &unidadesFuncionais.ufMul[disponivel];
        }
        if(tipoUF_inst==INT){
            unidadesFuncionais.ufInt[disponivel].busy = 1;
            unidadesFuncionais.ufInt[disponivel].fi = bancoRegs[regDestino];
            unidadesFuncionais.ufInt[disponivel].fj = bancoRegs[getRegistradorFonte1(ir)];
            unidadesFuncionais.ufInt[disponivel].fk = bancoRegs[getRegistradorFonte2(ir)];
            unidadesFuncionais.ufInt[disponivel].operacao = getOpcode(ir);
            unidadesFuncionais.ufInt[disponivel].qj = vetorResultados[getRegistradorFonte1(ir)];
            unidadesFuncionais.ufInt[disponivel].qk = vetorResultados[getRegistradorFonte2(ir)];
            unidadesFuncionais.ufInt[disponivel].rj = (unidadesFuncionais.ufInt[disponivel].qj == 0);
            unidadesFuncionais.ufInt[disponivel].rk = (unidadesFuncionais.ufInt[disponivel].qk == 0);
            unidadesFuncionais.ufInt[disponivel].qtde_ciclos = -1;
            vetorResultados[regDestino] = &unidadesFuncionais.ufInt[disponivel];
        }
        ir = 0;
        statusI[pc].emissao = clock;
        //printf("\n%d\n", statusI[pc].emissao);
    }
    else{
        printf("\nNAO FOI POSSIVEL EMITIR A INSTRUCAO\n\n");
    }
}

void leituraDeOperandos(){
    for(int i=0; i<unidadesFuncionais.qtdeADD; i++){
        if(unidadesFuncionais.ufAdd[i].rj == 1 && unidadesFuncionais.ufAdd[i].rk == 1){
            unidadesFuncionais.ufAdd[i].rj == 0;
            unidadesFuncionais.ufAdd[i].rk == 0;
            unidadesFuncionais.ufAdd[i].qtde_ciclos = getCiclos(unidadesFuncionais.ufAdd[i].operacao); 
        }
    }
    for(int i=0; i<unidadesFuncionais.qtdeMUL; i++){
        if(unidadesFuncionais.ufMul[i].rj == 1 && unidadesFuncionais.ufMul[i].rk == 1){
            unidadesFuncionais.ufMul[i].rj == 0;
            unidadesFuncionais.ufMul[i].rk == 0;
            unidadesFuncionais.ufMul[i].qtde_ciclos = getCiclos(unidadesFuncionais.ufMul[i].operacao);
        }
    }
    for(int i=0; i<unidadesFuncionais.qtdeINT; i++){
        if(unidadesFuncionais.ufInt[i].rj == 1 && unidadesFuncionais.ufInt[i].rk == 1 && unidadesFuncionais.ufInt[i].busy == 1){
            unidadesFuncionais.ufInt[i].rj == 0;
            unidadesFuncionais.ufInt[i].rk == 0;
            unidadesFuncionais.ufInt[i].qtde_ciclos = getCiclos(unidadesFuncionais.ufInt[i].operacao);
            printf("\n%d", unidadesFuncionais.ufInt[i].qtde_ciclos);
            printf("\n\nLEU");
        }
    }
}

void execucao(){
    for(int i=0; i<unidadesFuncionais.qtdeADD; i++){
        if(unidadesFuncionais.ufAdd[i].qtde_ciclos!=0 && unidadesFuncionais.ufAdd[i].qtde_ciclos!=-1){
            unidadesFuncionais.ufAdd[i].qtde_ciclos--;
        }
        else if(unidadesFuncionais.ufAdd[i].qtde_ciclos==0){
            executaInstrucao(unidadesFuncionais.ufAdd[i].fi, unidadesFuncionais.ufAdd[i].fj, unidadesFuncionais.ufAdd[i].fk, unidadesFuncionais.ufAdd[i].operacao);
            
        }
    }
    for(int i=0; i<unidadesFuncionais.qtdeMUL; i++){
        if(unidadesFuncionais.ufMul[i].qtde_ciclos!=0 && unidadesFuncionais.ufMul[i].qtde_ciclos!=-1){
            unidadesFuncionais.ufMul[i].qtde_ciclos--;
        }
        else if(unidadesFuncionais.ufMul[i].qtde_ciclos==0){
            executaInstrucao(unidadesFuncionais.ufMul[i].fi, unidadesFuncionais.ufMul[i].fj, unidadesFuncionais.ufMul[i].fk, unidadesFuncionais.ufMul[i].operacao);

        }
    }
    for(int i=0; i<unidadesFuncionais.qtdeINT; i++){
        if(unidadesFuncionais.ufInt[i].qtde_ciclos!=0 && unidadesFuncionais.ufInt[i].qtde_ciclos!=-1){
            unidadesFuncionais.ufInt[i].qtde_ciclos--;
        }
        else if(unidadesFuncionais.ufInt[i].qtde_ciclos==0){
            executaInstrucao(unidadesFuncionais.ufInt[i].fi, unidadesFuncionais.ufInt[i].fj, unidadesFuncionais.ufInt[i].fk, unidadesFuncionais.ufInt[i].operacao);

        }
    }
}

void escritaResultados(){
    for(int i=0; i<unidadesFuncionais.qtdeADD; i++){
        for(int j=0; j<unidadesFuncionais.qtdeMUL; j++){
            if((unidadesFuncionais.ufAdd[i].fi!=unidadesFuncionais.ufMul[j].fj)){
                
            }
        }
    }
}
