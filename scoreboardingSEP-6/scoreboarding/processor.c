#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "processor.h"
#include "registradores.h"
#include "unidade_funcional.h"
#include "scoreboarding.h"
#include "main.h"
int instrucoesEmitidas = 0;
int instrucoesEfetivadas = 0;

int buscaInstrucao(){
    printf("\n-------------BUSCA--------------\n");
    if(!stalled){
        colocaBarramento(memoria[pc]);
        ir = pegaBarramento();
        statusI[((pc%100)/4)].busca = clocki;
        if(getOpcode(ir)==13){
            pc = getImm(ir);
        }
        else if(getOpcode(ir)>=9 && getOpcode(ir)<=12){
            stalled=1;
            //desvio condicional 

        }
        else if(getOpcode(ir)==16){
            stalled = 1;
        }
        else{
            pc = pc+4;
            printf("\nBUSCOU: %d", ir);
        }
    }
    else{
        printf("\nSTALL");
    }
    printf("\n---------------------\n");
}

int getOpcode(int instrucao){
    int codOpcode = (instrucao >> 26) & 0x3F;
    return codOpcode;
} 

//PARA AS INSTRUCOES DE LOAD E STORE:::: RT É DESTINO, IMM É FONTE1 E R2 É FONTE2

//PARA INSTRUÇÕES DE SALTO O DESTINO FOI UTILIZADO PARA ARMAZENAR O IMM
int getRegistradorDestino(int instrucao){
    int destino;
    if(getOpcode(instrucao)==0 || getOpcode(instrucao)==2 || getOpcode(instrucao)==4 || getOpcode(instrucao)==5 || getOpcode(instrucao)==6 || getOpcode(instrucao)==7 || getOpcode(instrucao)==8){
        destino = (instrucao >> 11) & 0x1F;
    }
    else if(getOpcode(instrucao)==1 || getOpcode(instrucao)==3 || getOpcode(instrucao)==14 || getOpcode(instrucao)==15){
        destino = (instrucao >> 16) & 0x1F;
    }
    else if(getOpcode(instrucao)==9 || getOpcode(instrucao)==10 || getOpcode(instrucao)==11 || getOpcode(instrucao)==12 || getOpcode(instrucao)==13){
        destino = (instrucao >> 16) & 0x1F;
    }
    //printf("\nDESTINO: %d", destino);
    return destino;    
} 

int getRegistradorFonte1(int instrucao){
    int fonte1;
    if(getOpcode(instrucao)!=13 && getOpcode(instrucao)!=14 && getOpcode(instrucao)!=15 && getOpcode(instrucao)!=16)
        fonte1 = (instrucao >> 21) & 0x1F;
    else if(getOpcode(instrucao)==14 || getOpcode(instrucao)==15){
        fonte1 = instrucao & 0xFFFF;
    }
    //printf("\nFONTE1: %d", fonte1);
    return fonte1;    
} 

int getRegistradorFonte2(int instrucao){
    int fonte2;
    if(getOpcode(instrucao)!=1 && getOpcode(instrucao)!=3 && getOpcode(instrucao)!=8 && getOpcode(instrucao)!=13 && getOpcode(instrucao)!=14 && getOpcode(instrucao)!=15)
        fonte2 = (instrucao >> 16) & 0x1F;
    else if(getOpcode(instrucao)==14 || getOpcode(instrucao)==15){
        fonte2 = (instrucao >> 21) & 0x1F;
    }
    //printf("\nFONTE2: %d", fonte2);
    return fonte2;    
}

int getImm(int instrucao){
    int imm;
    if(getOpcode(instrucao)==13){
        imm = instrucao & 0x1FFFFFF;
    }
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

//FALTA GERENCIAR O STALL
int executaInstrucao(int destino, int fonte1, int fonte2, int opcode){
    int resultado=0;
    //printf("\nOPCODE: %d, DESTINO: %d, FONTE1: %d, FONTE2: %d", opcode, destino, fonte1, fonte2);
    if(opcode==0){
        //printf("\nESCREVEU r%d = r%d + r%d", destino, fonte1, fonte2);
        //bancoRegs[destino] = bancoRegs[fonte1] + bancoRegs[fonte2];
        destino = destino << 26;
        resultado = resultado | destino;
        int valor = bancoRegs[fonte1] + bancoRegs[fonte2];
        if(valor!= abs(valor)){
        	int sinal = 1;
        	sinal = sinal << 25;
        	resultado = resultado | sinal;
		}	
        valor = abs(valor) << 0;
        resultado = resultado | valor;
        //printf("\nRESULTADO Add= %d", resultado);
        return resultado;
    }
    else if(opcode==1){
        //printf("\nESCREVEU r%d = r%d + %d", destino, fonte1, fonte2);
        //bancoRegs[destino] = bancoRegs[fonte1] + fonte2;
        destino = destino << 26;
        resultado = resultado | destino;
        int valor = bancoRegs[fonte1] + fonte2;;
        if(valor!= abs(valor)){
        	int sinal = 1;
        	sinal = sinal << 25;
        	resultado = resultado | sinal;
		}	
        valor = abs(valor) << 0;
        resultado = resultado | valor;
        return resultado;
    }
    else if(opcode==2){
        //printf("\nESCREVEU r%d = r%d - r%d", destino, fonte1, fonte2);
       //bancoRegs[destino] = bancoRegs[fonte1] - bancoRegs[fonte2];
       destino = destino << 26;
       resultado = resultado | destino;
        int valor = bancoRegs[fonte1] - bancoRegs[fonte2];
        if(valor!= abs(valor)){
        	int sinal = 1;
        	sinal = sinal << 25;
        	resultado = resultado | sinal;
		}	
        valor = abs(valor) << 0;
        resultado = resultado | valor;
        return resultado;
    }
    else if(opcode==3){
        //printf("\nESCREVEU r%d = r%d - %d", destino, fonte1, fonte2);
        //bancoRegs[destino] = bancoRegs[fonte1] - fonte2;
        resultado = destino << 26;
        int valor = bancoRegs[fonte1] - bancoRegs[fonte2];
        if(valor!= abs(valor)){
        	int sinal = 1;
        	sinal = sinal << 25;
        	resultado = resultado | sinal;
		}	
        valor = abs(valor) << 0;
        resultado = resultado | valor;
        return resultado;
    }
    else if(opcode==4){
        //printf("\nESCREVEU r%d = r%d * r%d", destino, fonte1, fonte2);
        //bancoRegs[destino] = bancoRegs[fonte1] * bancoRegs[fonte2];
        resultado = destino << 26;
        int valor = bancoRegs[fonte1] * bancoRegs[fonte2];
        if(valor!= abs(valor)){
        	int sinal = 1;
        	sinal = sinal << 25;
        	resultado = resultado | sinal;
		}	
        valor = abs(valor) << 0;
        resultado = resultado | valor;
        return resultado;
    }
    else if(opcode==5){
        //printf("\nESCREVEU r%d = r%d / r%d", destino, fonte1, fonte2);
        //bancoRegs[destino] = bancoRegs[fonte1] / bancoRegs[fonte2];
        resultado = destino << 26;
        int valor = bancoRegs[fonte1] / bancoRegs[fonte2];
        if(valor!= abs(valor)){
        	int sinal = 1;
        	sinal = sinal << 25;
        	resultado = resultado | sinal;
		}	
        valor = abs(valor) << 0;
        resultado = resultado | valor;
        return resultado;
    }
    else if(opcode==6){
        //printf("\nESCREVEU r%d = r%d + r%d", destino, fonte1, fonte2);
        //bancoRegs[destino] = bancoRegs[fonte1] & bancoRegs[fonte2];
        resultado = destino << 26;
        int valor = bancoRegs[fonte1] && bancoRegs[fonte2];
        if(valor!= abs(valor)){
        	int sinal = 1;
        	sinal = sinal << 25;
        	resultado = resultado | sinal;
		}	
        valor = abs(valor) << 0;
        resultado = resultado | valor;
        return resultado;
    }
    else if(opcode==7){
        //printf("\nESCREVEU r%d = r%d | r%d", destino, fonte1, fonte2);
        //bancoRegs[destino] = bancoRegs[fonte1] | bancoRegs[fonte2];
        resultado = destino << 26;
        int valor = bancoRegs[fonte1] | bancoRegs[fonte2];
        if(valor!= abs(valor)){
        	int sinal = 1;
        	sinal = sinal << 25;
        	resultado = resultado | sinal;
		}	
        valor = abs(valor) << 0;
        resultado = resultado | valor;
        return resultado;
    }
    else if(opcode==8){
        //printf("\nESCREVEU r%d = -r%d", destino, fonte1);
        //bancoRegs[destino] = -1 * bancoRegs[fonte1];
        resultado = destino << 26;
        int valor = (-1) * bancoRegs[fonte1];
        if(valor!= abs(valor)){
        	int sinal = 1;
        	sinal = sinal << 25;
        	resultado = resultado | sinal;
		}	
        valor = abs(valor) << 0;
        resultado = resultado | valor;
        return resultado;
    }
    else if(opcode==9){
        if(bancoRegs[fonte1]<bancoRegs[fonte2]){
            //pc = pc + 4 + destino;
            int valor = pc + 4 + destino;
            destino=32;
            resultado = destino << 26;
            if(valor!= abs(valor)){
                int sinal = 1;
                sinal = sinal << 25;
                resultado = resultado | sinal;
            }	
            valor = abs(valor) << 0;
            resultado = resultado | valor;
            return resultado;
                
        }
    }
    else if(opcode==10){
        if(bancoRegs[fonte1]>bancoRegs[fonte2]){
            //pc = pc + 4 + destino;
            int valor = pc + 4 + destino;
            destino=32;
            resultado = destino << 26;
            if(valor!= abs(valor)){
                int sinal = 1;
                sinal = sinal << 25;
                resultado = resultado | sinal;
            }	
            valor = abs(valor) << 0;
            resultado = resultado | valor;
            return resultado;
        }
    }
    else if(opcode==11){
        if(bancoRegs[fonte1]==bancoRegs[fonte2]){
            //pc = pc + 4 + destino;
            int valor = pc + 4 + destino;
            destino=32;
            resultado = destino << 26;
            if(valor!= abs(valor)){
                int sinal = 1;
                sinal = sinal << 25;
                resultado = resultado | sinal;
            }	
            valor = abs(valor) << 0;
            resultado = resultado | valor;
            return resultado;
        }
    }
    else if(opcode==12){
        if(bancoRegs[fonte1]!=bancoRegs[fonte2]){
            //pc = pc + 4 + destino;
            int valor = pc + 4 + destino;
            destino=32;
            resultado = destino << 26;
            if(valor!= abs(valor)){
                int sinal = 1;
                sinal = sinal << 25;
                resultado = resultado | sinal;
            }	
            valor = abs(valor) << 0;
            resultado = resultado | valor;
            return resultado;
        }
    }
    //SALTO INCONDICIONAL (OPCODE 13) TEM QUE SER VISTO NA BUSCAAAAAAAAAA
    else if(opcode==14){
        //printf("\nEXECUTOU r%d = memoria[%d + r%d]\n", destino, fonte1, fonte2);
        //bancoRegs[destino] = memoria[fonte1 + bancoRegs[fonte2]];
            destino = destino << 26;
            resultado = resultado | destino;
            int valor = memoria[fonte1 + bancoRegs[fonte2]];
            if(valor!= abs(valor)){
                int sinal = 1;
                sinal = sinal << 25;
                resultado = resultado | sinal;
            }	
            valor = abs(valor) << 0;
            resultado = resultado | valor;
            printf("\nRESULTADO lw = %d", resultado);
            return resultado;
    }
    else if(opcode==15){
        //printf("\nEXECUTOu memoria[%d + r%d] = r%d\n", fonte1, fonte2, destino);
        //memoria[bancoRegs[fonte1] + fonte2] = bancoRegs[destino];
        int valor = bancoRegs[destino];
        int endereco = bancoRegs[fonte1] + fonte2;
        destino = 33;
        resultado = destino << 26;
        endereco = endereco << 25;
        resultado = resultado | endereco;
            if(valor!= abs(valor)){
                int sinal = 1;
                sinal = sinal << 15;
                resultado = resultado | sinal;
            }	
            valor = abs(valor) << 0;
            resultado = resultado | valor;
            return resultado;
    }
}

void escreveNoDestino(int resultado){
     int mascara_destino = 0xFC000000; // 11111100000000000000000000000000 em binário
    // Extrai os 6 bits mais significativos (destino)
    int bits_destino = (resultado >> 26) & 0x3F;
    //printf("\n\nbits destino: %d", bits_destino);
    // Limpa os 6 bits mais significativos do resultado (obtendo o "resto")
    int resto = resultado & ~mascara_destino;

    if (bits_destino>=0 && bits_destino<=31){
        printf("INSERINDO %d em REGISTRADOR %d\n",resto,bits_destino);
        bancoRegs[bits_destino]=resto;
    }
    else if(bits_destino==32){
        printf("INSERINDO em pc o valor %d\n",resto);
        pc=resto;
    }
    else if(bits_destino==33){
        // Extract bits 25 to 16 for the address
        int endereco = (resultado >> 16) & 0x3FF;  // 0x3FF represents 10 bits set to 1

        // Extract bits 15 to 0 for the value to be written
        int valor = resultado & 0xFFFF;  // 0xFFFF represents 16 bits set to 1

        if(endereco%4!=0 && endereco>99){
            printf("ENDEREÇO DE MEMORIA INVALIDO.\n");
            printf("NAO FOI POSSIVEL INSERIR %d em memoria[%d].\n",valor,endereco);
        }
        else{
            memoria[endereco]=valor;
        }
        
    }


}

//DEPOIS DE JOGAR AS INSTRUCOES PRA UF EU COLOCO OS DADOS E FAÇO A QUANTIDADE DE CICLOS = -1 
//PRA SINALIZAR QUE A LEITURA DE OPERANDOS AINDA NAO FOI FEITA E A EXECUCAO AINDA NAO PODE COMECAR

//DUVIDAS:::: DEPOIS DOS RESULTADOS ESTAREM PRONTOS QJ E QK ANULA?; NAO SEI DIREITO AINDA COMO VAI FUNCIONAR O VETORRESULTADOS
void emiteInstrucao(){
    printf("\n----------------EMISSAO--------------\n");
    if(ir!=0 && ir!=1073741824){
        int regDestino = getRegistradorDestino(ir);
        int tipoUF_inst = getTipoUF(ir);
        int disponivel = getUFdisponivel(tipoUF_inst);
        //printf("\nUF DISPONIVEL DO TIPO %d = %d", tipoUF_inst, disponivel);
        if(vetorResultados[regDestino] == NULL && disponivel!=-1){
            //printf("%p", vetorResultados[1]);
            if(tipoUF_inst==0){
                unidadesFuncionais.ufAdd[disponivel].instrucao=ir;
                unidadesFuncionais.ufAdd[disponivel].busy = 1;
                unidadesFuncionais.ufAdd[disponivel].fi = regDestino;
                unidadesFuncionais.ufAdd[disponivel].fj = getRegistradorFonte1(ir);
                unidadesFuncionais.ufAdd[disponivel].fk = getRegistradorFonte2(ir);
                unidadesFuncionais.ufAdd[disponivel].operacao = getOpcode(ir);
                unidadesFuncionais.ufAdd[disponivel].qj = vetorResultados[getRegistradorFonte1(ir)];
                unidadesFuncionais.ufAdd[disponivel].qk = vetorResultados[getRegistradorFonte2(ir)];
                //printf("\n\nQk: %p\n\n", unidadesFuncionais.ufAdd[disponivel].qk);
                unidadesFuncionais.ufAdd[disponivel].rj = (unidadesFuncionais.ufAdd[disponivel].qj == 0);
                unidadesFuncionais.ufAdd[disponivel].rk = (unidadesFuncionais.ufAdd[disponivel].qk == 0);
                unidadesFuncionais.ufAdd[disponivel].qtde_ciclos = -1;
                vetorResultados[regDestino] = &unidadesFuncionais.ufAdd[disponivel];
            }
            else if(tipoUF_inst==1){
                unidadesFuncionais.ufMul[disponivel].instrucao=ir;
                unidadesFuncionais.ufMul[disponivel].busy = 1;
                unidadesFuncionais.ufMul[disponivel].fi = regDestino;
                unidadesFuncionais.ufMul[disponivel].fj = getRegistradorFonte1(ir);
                unidadesFuncionais.ufMul[disponivel].fk = getRegistradorFonte2(ir);
                unidadesFuncionais.ufMul[disponivel].operacao = getOpcode(ir);
                unidadesFuncionais.ufMul[disponivel].qj = vetorResultados[getRegistradorFonte1(ir)];
                unidadesFuncionais.ufMul[disponivel].qk = vetorResultados[getRegistradorFonte2(ir)];
                unidadesFuncionais.ufMul[disponivel].rj = (unidadesFuncionais.ufMul[disponivel].qj == 0);
                unidadesFuncionais.ufMul[disponivel].rk = (unidadesFuncionais.ufMul[disponivel].qk == 0);
                unidadesFuncionais.ufMul[disponivel].qtde_ciclos = -1;
                vetorResultados[regDestino] = &unidadesFuncionais.ufMul[disponivel];
            }
            else if(tipoUF_inst==2){
                unidadesFuncionais.ufInt[disponivel].instrucao=ir;
                unidadesFuncionais.ufInt[disponivel].busy = 1;
                unidadesFuncionais.ufInt[disponivel].fi = regDestino;
                unidadesFuncionais.ufInt[disponivel].fj = getRegistradorFonte1(ir);
                unidadesFuncionais.ufInt[disponivel].fk = getRegistradorFonte2(ir);
                unidadesFuncionais.ufInt[disponivel].operacao = getOpcode(ir);
                unidadesFuncionais.ufInt[disponivel].qj = vetorResultados[getRegistradorFonte1(ir)];
                unidadesFuncionais.ufInt[disponivel].qk = vetorResultados[getRegistradorFonte2(ir)];
                unidadesFuncionais.ufInt[disponivel].rj = (unidadesFuncionais.ufInt[disponivel].qj == NULL);
                unidadesFuncionais.ufInt[disponivel].rk = (unidadesFuncionais.ufInt[disponivel].qk == NULL);
                unidadesFuncionais.ufInt[disponivel].qtde_ciclos = -1;
                //printf("\nAAAAAAAAAAAAAA\n");
                //printf("FI: %d", unidadesFuncionais.ufInt[disponivel].fi);
                vetorResultados[regDestino] = &unidadesFuncionais.ufInt[disponivel];
            }
            printf("\nEMITIU %d", ir);
            instrucoesEmitidas++;
            statusI[getIndiceInstrucao(ir)].emissao = clocki;
            ir = 0;
            stalled = 0;
            //printf("\n%d\n", statusI[pc].emissao);
        }
        else{
            stalled = 1;
            printf("\nNAO FOI POSSIVEL EMITIR A INSTRUCAO\n\n");
        }
    }
    else{
        printf("\nNão houve emissão");
    }
    printf("\n-----------------------------\n");
}

void leituraDeOperandos(){
    printf("\n-------------------LEITURA OPS------------------\n");
    for(int i=0; i<unidadesFuncionais.qtdeADD; i++){
        printf("\n\nrj: %d; rk: %d", unidadesFuncionais.ufAdd[i].rj, unidadesFuncionais.ufAdd[i].rk);
        if(unidadesFuncionais.ufAdd[i].rj == 1 && unidadesFuncionais.ufAdd[i].rk == 1){
            unidadesFuncionais.ufAdd[i].rj = 0;
            unidadesFuncionais.ufAdd[i].rk = 0;
            unidadesFuncionais.ufAdd[i].qtde_ciclos = getCiclos(unidadesFuncionais.ufAdd[i].operacao);
            //printf("\nVIROU: rj: %d; rk: %d", unidadesFuncionais.ufAdd[i].rj, unidadesFuncionais.ufAdd[i].rk);
            printf("\nINST= %d", unidadesFuncionais.ufAdd[i].instrucao);
            statusI[getIndiceInstrucao(unidadesFuncionais.ufAdd[i].instrucao)].leitura_op = clocki;
            printf("LEU %d %d %d", unidadesFuncionais.ufAdd[i].fi, unidadesFuncionais.ufAdd[i].fj, unidadesFuncionais.ufAdd[i].fk);
        }
    }
    for(int i=0; i<unidadesFuncionais.qtdeMUL; i++){
        if(unidadesFuncionais.ufMul[i].rj == 1 && unidadesFuncionais.ufMul[i].rk == 1){
            unidadesFuncionais.ufMul[i].rj = 0;
            unidadesFuncionais.ufMul[i].rk = 0;
            unidadesFuncionais.ufMul[i].qtde_ciclos = getCiclos(unidadesFuncionais.ufMul[i].operacao);
            statusI[getIndiceInstrucao(unidadesFuncionais.ufMul[i].instrucao)].leitura_op = clocki;
            printf("LEU %d %d %d", unidadesFuncionais.ufMul[i].fi, unidadesFuncionais.ufMul[i].fj, unidadesFuncionais.ufMul[i].fk);
        }
    }
    for(int i=0; i<unidadesFuncionais.qtdeINT; i++){
        if(unidadesFuncionais.ufInt[i].rj == 1 && unidadesFuncionais.ufInt[i].rk == 1){
            unidadesFuncionais.ufInt[i].rj = 0;
            unidadesFuncionais.ufInt[i].rk = 0;
            unidadesFuncionais.ufInt[i].qtde_ciclos = getCiclos(unidadesFuncionais.ufInt[i].operacao);
            statusI[getIndiceInstrucao(unidadesFuncionais.ufInt[i].instrucao)].leitura_op = clocki;
            printf("LEU %d %d %d", unidadesFuncionais.ufInt[i].fi, unidadesFuncionais.ufInt[i].fj, unidadesFuncionais.ufInt[i].fk);
        }
    }
    printf("\n-----------------------------\n");
}

//TALVEZ SEJA MELHOR SÓ SIMULAR A EXECUCAO E FAZER ELA DE FATO SÓ NA ESCRITA DE RESULTADOS
void execucao(){
    printf("\n----------EXECUCAO-----------\n");
    for(int i=0; i<unidadesFuncionais.qtdeADD; i++){
        if(unidadesFuncionais.ufAdd[i].qtde_ciclos!=0 && unidadesFuncionais.ufAdd[i].qtde_ciclos!=-1){
            if(statusI[getIndiceInstrucao(unidadesFuncionais.ufAdd[i].instrucao)].execucao==0){
                statusI[getIndiceInstrucao(unidadesFuncionais.ufAdd[i].instrucao)].execucao=clocki;
            }
            unidadesFuncionais.ufAdd[i].qtde_ciclos--;
            printf("\nADD%d FALTAM %d CICLOS\n", i, unidadesFuncionais.ufAdd[i].qtde_ciclos);
        }
        if(unidadesFuncionais.ufAdd[i].qtde_ciclos==0 && (unidadesFuncionais.ufAdd[i].fi!=0 && unidadesFuncionais.ufAdd[i].fj!=0 && unidadesFuncionais.ufAdd[i].fk!=0)){
            int resultado = executaInstrucao(unidadesFuncionais.ufAdd[i].fi, unidadesFuncionais.ufAdd[i].fj, unidadesFuncionais.ufAdd[i].fk, unidadesFuncionais.ufAdd[i].operacao);
            unidadesFuncionais.ufAdd[i].qtde_ciclos = 0;
            //acho que tem que fazer resultado ser resultado+destino
            //possiveis exemplos: bits resultado e bits para registrador ou pc ou memoria 
            //se for registrador, é de 0 a 31, se for pc pode ser 32 e memoria 33 ou qualquer outra coisa q kiser decidir 
            colocaBarramentoResultados(resultado);
        }
    }
    for(int i=0; i<unidadesFuncionais.qtdeMUL; i++){
        if(unidadesFuncionais.ufMul[i].qtde_ciclos!=0 && unidadesFuncionais.ufMul[i].qtde_ciclos!=-1){
            if(statusI[getIndiceInstrucao(unidadesFuncionais.ufMul[i].instrucao)].execucao==0){
                statusI[getIndiceInstrucao(unidadesFuncionais.ufMul[i].instrucao)].execucao=clocki;
            }
            unidadesFuncionais.ufMul[i].qtde_ciclos--;
            printf("\nMUL%d FALTAM %d CICLOS\n", i, unidadesFuncionais.ufMul[i].qtde_ciclos);
        }
        if(unidadesFuncionais.ufMul[i].qtde_ciclos==0 && (unidadesFuncionais.ufMul[i].fi!=0 && unidadesFuncionais.ufMul[i].fj!=0 && unidadesFuncionais.ufMul[i].fk!=0)){
            //executaInstrucao(unidadesFuncionais.ufMul[i].fi, unidadesFuncionais.ufMul[i].fj, unidadesFuncionais.ufMul[i].fk, unidadesFuncionais.ufMul[i].operacao);
            unidadesFuncionais.ufMul[i].qtde_ciclos = 0;
            int resultado = executaInstrucao(unidadesFuncionais.ufMul[i].fi, unidadesFuncionais.ufMul[i].fj, unidadesFuncionais.ufMul[i].fk, unidadesFuncionais.ufMul[i].operacao);
            colocaBarramentoResultados(resultado);
        }
    }
    for(int i=0; i<unidadesFuncionais.qtdeINT; i++){
        if(i==0){
            //printf("\nAAAAAAAAAAAAAAAAA");
            //printf("FI: %d, FJ: %d, FK: %d", unidadesFuncionais.ufInt[i].fi, unidadesFuncionais.ufInt[i].fj, unidadesFuncionais.ufInt[i].fk);
        }
        if(unidadesFuncionais.ufInt[i].qtde_ciclos!=0 && unidadesFuncionais.ufInt[i].qtde_ciclos!=-1){
            if(statusI[getIndiceInstrucao(unidadesFuncionais.ufInt[i].instrucao)].execucao==0){
                statusI[getIndiceInstrucao(unidadesFuncionais.ufInt[i].instrucao)].execucao=clocki;
            }
            unidadesFuncionais.ufInt[i].qtde_ciclos--;
            printf("\nINT%d FALTAM %d CICLOS\n", i, unidadesFuncionais.ufInt[i].qtde_ciclos);
        }
        if(unidadesFuncionais.ufInt[i].qtde_ciclos==0 && (unidadesFuncionais.ufInt[i].fi!=0 && unidadesFuncionais.ufInt[i].fj!=0 && unidadesFuncionais.ufInt[i].fk!=0)){
            //executaInstrucao(unidadesFuncionais.ufInt[i].fi, unidadesFuncionais.ufInt[i].fj, unidadesFuncionais.ufInt[i].fk, unidadesFuncionais.ufInt[i].operacao);
            if(i==0){
                //printf("\nAAAAAAAAAAAAAAAAA");
                //printf("FI: %d, FJ: %d, FK: %d", unidadesFuncionais.ufInt[i].fi, unidadesFuncionais.ufInt[i].fj, unidadesFuncionais.ufInt[i].fk);
            }
            //unidadesFuncionais.ufInt[i].qtde_ciclos = 0;
            int resultado = executaInstrucao(unidadesFuncionais.ufInt[i].fi, unidadesFuncionais.ufInt[i].fj, unidadesFuncionais.ufInt[i].fk, unidadesFuncionais.ufInt[i].operacao);
            printf("\nresultado: %d", resultado);
            colocaBarramentoResultados(resultado);
            printf("\nBARRAMENTO RESULTS: %d", barramentoResultados);

        }
    }
    printf("\n-----------------\n");
}


//TEMOS QUE LEVAR EM CONSIDERAÇÃO QUE INSTRUÇÕES DE STORE E SALTO NÃO TEM RAW ENTAO SEMPRE PODE ESCREVER
void escritaResultados(){
    printf("\n-----------------ESCRITA---------------\n");
    int checkAddA=1, checkAddB=1, checkAddC=1;
    int checkIntA=1, checkIntB=1, checkIntC=1;
    int checkMulA=1, checkMulB=1, checkMulC=1;

    for(int i=0; i<unidadesFuncionais.qtdeADD; i++){
        if(unidadesFuncionais.ufAdd[i].qtde_ciclos == 0){
            for(int j=0; j<unidadesFuncionais.qtdeMUL; j++){
                if(((unidadesFuncionais.ufAdd[i].fi!=unidadesFuncionais.ufMul[j].fj) || unidadesFuncionais.ufMul[j].rj==0)
                && (unidadesFuncionais.ufAdd[i].fi!=unidadesFuncionais.ufMul[j].fk) || unidadesFuncionais.ufMul[j].rk==0){
                    if(unidadesFuncionais.ufMul[j].qj==&unidadesFuncionais.ufAdd[i]){
                        unidadesFuncionais.ufMul[j].rj = 1;
                    }
                    if(unidadesFuncionais.ufMul[j].qk==&unidadesFuncionais.ufAdd[i]){
                        unidadesFuncionais.ufMul[j].rk = 1;
                    }
                }
                else{
                    checkAddA = 0;
                }
            }
            for(int j=0; j<unidadesFuncionais.qtdeINT; j++){
                if(((unidadesFuncionais.ufAdd[i].fi!=unidadesFuncionais.ufInt[j].fj) || unidadesFuncionais.ufInt[j].rj==0)
                && (unidadesFuncionais.ufAdd[i].fi!=unidadesFuncionais.ufInt[j].fk) || unidadesFuncionais.ufInt[j].rk==0){
                    if(unidadesFuncionais.ufInt[j].qj==&unidadesFuncionais.ufAdd[i]){
                        unidadesFuncionais.ufInt[j].rj = 1;
                    }
                    if(unidadesFuncionais.ufInt[j].qk==&unidadesFuncionais.ufAdd[i]){
                        unidadesFuncionais.ufInt[j].rk = 1;
                    }
                }
                else{
                    checkAddB = 0;
                }
            }
            for(int j=0; j<unidadesFuncionais.qtdeADD; j++){
                if((((unidadesFuncionais.ufAdd[i].fi!=unidadesFuncionais.ufAdd[j].fj) || unidadesFuncionais.ufAdd[j].rj==0)
                && (unidadesFuncionais.ufAdd[i].fi!=unidadesFuncionais.ufAdd[j].fk) || unidadesFuncionais.ufAdd[j].rk==0)){
                    if(i!=j){
                        if(unidadesFuncionais.ufAdd[j].qj==&unidadesFuncionais.ufAdd[i]){
                            unidadesFuncionais.ufAdd[j].rj = 1;
                        }
                        if(unidadesFuncionais.ufAdd[j].qk==&unidadesFuncionais.ufAdd[i]){
                            unidadesFuncionais.ufAdd[j].rk = 1;
                        }
                    }
                }
                else{
                    checkAddC = 0;
                }
            }
            if(checkAddA && checkAddB && checkAddC && unidadesFuncionais.ufAdd[i].qtde_ciclos == 0 &&
            (unidadesFuncionais.ufAdd[i].fi != 0 && unidadesFuncionais.ufAdd[i].fj != 0 && unidadesFuncionais.ufAdd[i].fk !=0)){
                vetorResultados[unidadesFuncionais.ufAdd[i].fi] = 0;
                //printf("FI: %d; FJ: %d, FK: %d", unidadesFuncionais.ufAdd[i].fi, unidadesFuncionais.ufAdd[i].fj, unidadesFuncionais.ufAdd[i].fk);
                //executaInstrucao(unidadesFuncionais.ufAdd[i].fi, unidadesFuncionais.ufAdd[i].fj, unidadesFuncionais.ufAdd[i].fk, unidadesFuncionais.ufAdd[i].operacao);
                escreveNoDestino(pegaBarramentoResultados());
                statusI[getIndiceInstrucao(unidadesFuncionais.ufAdd[i].instrucao)].escrita=clocki;
                unidadesFuncionais.ufAdd[i].instrucao=0;
                unidadesFuncionais.ufAdd[i].busy = 0;
                unidadesFuncionais.ufAdd[i].fi = 0;
                unidadesFuncionais.ufAdd[i].fj = 0;
                unidadesFuncionais.ufAdd[i].fk = 0;
                unidadesFuncionais.ufAdd[i].operacao = 0;
                unidadesFuncionais.ufAdd[i].qj = NULL;
                unidadesFuncionais.ufAdd[i].qk = NULL;
                unidadesFuncionais.ufAdd[i].rj = 0;
                instrucoesEfetivadas++;
            }
        }
        checkAddA = 1;
        checkAddB = 1;
        checkAddC = 1;
    }
    for(int i=0; i<unidadesFuncionais.qtdeMUL; i++){
        for(int j=0; j<unidadesFuncionais.qtdeADD; j++){
            if(((unidadesFuncionais.ufMul[i].fi!=unidadesFuncionais.ufAdd[j].fj) || unidadesFuncionais.ufAdd[j].rj==0)
             && (unidadesFuncionais.ufMul[i].fi!=unidadesFuncionais.ufAdd[j].fk) || unidadesFuncionais.ufAdd[j].rk==0){
                if(unidadesFuncionais.ufAdd[j].qj==&unidadesFuncionais.ufMul[i]){
                    unidadesFuncionais.ufAdd[j].rj = 1;
                }
                if(unidadesFuncionais.ufAdd[j].qk==&unidadesFuncionais.ufMul[i]){
                    unidadesFuncionais.ufAdd[j].rk = 1;
                }
            }
            else{
                checkMulA = 0;
            }
        }
        for(int j=0; j<unidadesFuncionais.qtdeINT; j++){
            if(((unidadesFuncionais.ufMul[i].fi!=unidadesFuncionais.ufInt[j].fj) || unidadesFuncionais.ufInt[j].rj==0)
             && (unidadesFuncionais.ufMul[i].fi!=unidadesFuncionais.ufInt[j].fk) || unidadesFuncionais.ufInt[j].rk==0){
                if(unidadesFuncionais.ufInt[j].qj==&unidadesFuncionais.ufMul[i]){
                    unidadesFuncionais.ufInt[j].rj = 1;
                    unidadesFuncionais.ufInt[j].rk = 1;
                }
                if(unidadesFuncionais.ufInt[j].qk==&unidadesFuncionais.ufMul[i]){
                    unidadesFuncionais.ufInt[j].rk = 1;
                }
            }
            else{
                checkMulB = 0;
            }
        }
        for(int j=0; j<unidadesFuncionais.qtdeMUL; j++){
            if((((unidadesFuncionais.ufMul[i].fi!=unidadesFuncionais.ufMul[j].fj) || unidadesFuncionais.ufMul[j].rj==0)
             && (unidadesFuncionais.ufMul[i].fi!=unidadesFuncionais.ufMul[j].fk) || unidadesFuncionais.ufMul[j].rk==0)){
                if(i!=j){
                    if(unidadesFuncionais.ufMul[j].qj==&unidadesFuncionais.ufMul[i]){
                        unidadesFuncionais.ufMul[j].rj = 1;
                    }
                    if(unidadesFuncionais.ufMul[j].qk==&unidadesFuncionais.ufMul[i]){
                        unidadesFuncionais.ufMul[j].rk = 1;
                    }
                }
            }
            else{
                checkMulC = 0;
            }
        }
        if(checkMulA && checkMulB && checkMulC && unidadesFuncionais.ufMul[i].qtde_ciclos == 0 &&
        (unidadesFuncionais.ufMul[i].fi != 0 && unidadesFuncionais.ufMul[i].fj != 0 && unidadesFuncionais.ufMul[i].fk !=0)){
            vetorResultados[unidadesFuncionais.ufMul[i].fi] = 0;
            //executaInstrucao(unidadesFuncionais.ufMul[i].fi, unidadesFuncionais.ufMul[i].fj, unidadesFuncionais.ufMul[i].fk, unidadesFuncionais.ufMul[i].operacao);
            escreveNoDestino(pegaBarramentoResultados());
            statusI[getIndiceInstrucao(unidadesFuncionais.ufMul[i].instrucao)].escrita=clocki;
            unidadesFuncionais.ufMul[i].instrucao=0;
            unidadesFuncionais.ufMul[i].busy = 0;
            unidadesFuncionais.ufMul[i].fi = 0;
            unidadesFuncionais.ufMul[i].fj = 0;
            unidadesFuncionais.ufMul[i].fk = 0;
            unidadesFuncionais.ufMul[i].operacao = 0;
            unidadesFuncionais.ufMul[i].qj = NULL;
            unidadesFuncionais.ufMul[i].qk = NULL;
            unidadesFuncionais.ufMul[i].rj = 0;
            instrucoesEfetivadas++;
        }
        checkMulA = 1;
        checkMulB = 1;
        checkMulC = 1;
    }
    for(int i=0; i<unidadesFuncionais.qtdeINT; i++){
        if(unidadesFuncionais.ufInt[i].qtde_ciclos==0){
            for(int j=0; j<unidadesFuncionais.qtdeADD; j++){
                //printf("\nFI INT: %d, FJ ADD: %d, FK ADD: %d", unidadesFuncionais.ufInt[i].fi, unidadesFuncionais.ufInt[j].fj, unidadesFuncionais.ufInt[j].fk);
                //printf("\n%d, %d", ((unidadesFuncionais.ufInt[i].fi!=unidadesFuncionais.ufAdd[j].fj) || unidadesFuncionais.ufAdd[j].rj==0), ((unidadesFuncionais.ufInt[i].fi!=unidadesFuncionais.ufAdd[j].fk) || unidadesFuncionais.ufAdd[j].rk==0));
                if(((unidadesFuncionais.ufInt[i].fi!=unidadesFuncionais.ufAdd[j].fj) || unidadesFuncionais.ufAdd[j].rj==0)
                && ((unidadesFuncionais.ufInt[i].fi!=unidadesFuncionais.ufAdd[j].fk) || unidadesFuncionais.ufAdd[j].rk==0)){
                    //printf("\nQk: %p; UF: %p", unidadesFuncionais.ufAdd[j].qk, &unidadesFuncionais.ufInt[i]);
                    if(unidadesFuncionais.ufAdd[j].qj==&unidadesFuncionais.ufInt[i]){
                        unidadesFuncionais.ufAdd[j].rj = 1;
                    }
                    if(unidadesFuncionais.ufAdd[j].qk==&unidadesFuncionais.ufInt[i]){
                        unidadesFuncionais.ufAdd[j].rk = 1;
                    }
                }
                else{
                    checkIntA = 0;
                }
            }
            for(int j=0; j<unidadesFuncionais.qtdeMUL; j++){
                if(((unidadesFuncionais.ufInt[i].fi!=unidadesFuncionais.ufMul[j].fj) || unidadesFuncionais.ufMul[j].rj==0)
                && (unidadesFuncionais.ufInt[i].fi!=unidadesFuncionais.ufMul[j].fk) || unidadesFuncionais.ufMul[j].rk==0){
                    if(unidadesFuncionais.ufMul[j].qj==&unidadesFuncionais.ufInt[i]){
                        unidadesFuncionais.ufMul[j].rj = 1;
                    }
                    if(unidadesFuncionais.ufMul[j].qk==&unidadesFuncionais.ufInt[i]){
                        unidadesFuncionais.ufMul[j].rk = 1;
                    }
                }
                else{
                    checkIntB = 0;
                }
            }
            for(int j=0; j<unidadesFuncionais.qtdeINT; j++){
                if(i!=j){
                    if(((unidadesFuncionais.ufInt[i].fi!=unidadesFuncionais.ufInt[j].fj) || unidadesFuncionais.ufInt[j].rj==0)
                    && ((unidadesFuncionais.ufInt[i].fi!=unidadesFuncionais.ufInt[j].fk) || unidadesFuncionais.ufInt[j].rk==0)){
                        if(unidadesFuncionais.ufInt[j].qj==&unidadesFuncionais.ufInt[i]){
                            unidadesFuncionais.ufInt[j].rj = 1;
                        }
                        if(unidadesFuncionais.ufInt[j].qk==&unidadesFuncionais.ufInt[i]){
                            unidadesFuncionais.ufInt[j].rk = 1;
                        }
                    }
                    else{
                        checkIntC = 0;
                    }
                }
            }
            //printf("\n\nCHECK %d, %d, %d", unidadesFuncionais.ufInt[i].fi, unidadesFuncionais.ufInt[i].fj, unidadesFuncionais.ufInt[i].fk);
            //printf("\n\nCHECK %d, %d, %d", checkIntA, checkIntB, checkIntC);
            if(checkIntA && checkIntB && checkIntC && unidadesFuncionais.ufInt[i].qtde_ciclos == 0){
                //printf("\n\nCHECK %d, %d, %d", unidadesFuncionais.ufInt[i].fi, unidadesFuncionais.ufInt[i].fj, unidadesFuncionais.ufInt[i].fk);
                if((unidadesFuncionais.ufInt[i].fi == 0 && unidadesFuncionais.ufInt[i].fj == 0 && unidadesFuncionais.ufInt[i].fk ==0)){
                }
                else{
                    //printf("\n\nCHECK %d, %d, %d", unidadesFuncionais.ufInt[i].fi, unidadesFuncionais.ufInt[i].fj, unidadesFuncionais.ufInt[i].fk);
                    vetorResultados[unidadesFuncionais.ufInt[i].fi] = 0;
                    //executaInstrucao(unidadesFuncionais.ufInt[i].fi, unidadesFuncionais.ufInt[i].fj, unidadesFuncionais.ufInt[i].fk, unidadesFuncionais.ufInt[i].operacao);
                    //printf("\n BARRAMENTO: %d", pegaBarramento());
                    escreveNoDestino(pegaBarramentoResultados());
                    statusI[getIndiceInstrucao(unidadesFuncionais.ufInt[i].instrucao)].escrita=clocki;
                    unidadesFuncionais.ufInt[i].instrucao=0;
                    unidadesFuncionais.ufInt[i].busy = 0;
                    unidadesFuncionais.ufInt[i].fi = 0;
                    unidadesFuncionais.ufInt[i].fj = 0;
                    unidadesFuncionais.ufInt[i].fk = 0;
                    unidadesFuncionais.ufInt[i].operacao = 0;
                    unidadesFuncionais.ufInt[i].qj = NULL;
                    unidadesFuncionais.ufInt[i].qk = NULL;
                    unidadesFuncionais.ufInt[i].rj = 0;
                    instrucoesEfetivadas++;
                }
            }
        }
        checkIntA = 1;
        checkIntB = 1;
        checkIntC = 1;
    }
    printf("\n---------------------------\n");
}