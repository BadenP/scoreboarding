#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tradutor.h"
#include "memoria.h"
#include "registradores.h"
#include "main.h"
#include "unidade_funcional.h"
#include "scoreboarding.h"

int ciclosParaExecutar[16];
int clock;
int qtdeAdd, qtdeInt, qtdeMul;
int addCiclos, mulCiclos, lwCiclos, subCiclos, divCiclos, swCiclos, bgtCiclos, jCiclos;
int addiCiclos, subiCiclos, andCiclos, orCiclos, notCiclos, bltCiclos, beqCiclos, bneCiclos;

int getValor(const char *linha) {
    char *separador = strstr(linha, ":");
    if (separador != NULL) {
        int valor;
        sscanf(separador + 1, "%d", &valor);
        return valor;
    }
    return 0; // Caso não encontre o separador, retorna 0.
}

int leituraArquivo(char * file, int memsize, char * output){
//AQUI AINDA PRECISA FAZER COM QUE # SEJA ACEITO COMO UM COMENTÁRIO NO CÓDIGO
		FILE *arquivo;
	    char buffer[256];
		int dado;
		char *endptr;
	    // Abre o arquivo em modo de leitura
	    arquivo = fopen(file, "r");
	    //int memsize = atoi(argv[4]);
        inicializaMemoria(memsize);
		inicializaStatusInstrucoes();
	
	    if (arquivo == NULL) {
	        printf("Erro ao abrir o arquivo.\n");
	        
	    }
	    enum categoria { NENHUMA, UF, INST, PL, DADOS };
    	enum categoria categoria = NENHUMA;
    	
    	FILE* instrucoes;
		instrucoes = fopen("inst.txt", "w+");
	    
	    while(fgets(buffer, sizeof(buffer), arquivo)){
			if(buffer[0] == '#'){
				;
			}
		    // Verifica se a linha contém a palavra-chave "UF"
		    if (strcmp(buffer, "UF\n") == 0) {
		    	categoria = UF;
		    }
		    // Verifica se a linha contém a palavra-chave "INST"
		    else if (strcmp(buffer, "INST\n") == 0) {
		        categoria = INST;
		    }
		    else if(strcmp(buffer, ". data\n") == 0 || strcmp(buffer, ".data\n") == 0){
				categoria = DADOS;
			}
			else if(strcmp(buffer, ". text\n") == 0 || strcmp(buffer, ". text\n") == 0){
				categoria = PL;
				pc = 100;
			}
		    else if(strcmp(buffer, "*/\n") == 0){
		    	categoria = NENHUMA;
			}
		       
		    else {
            	int valor = 0;
            	if (categoria == INST || categoria == UF){
                    if (strstr(buffer, "addi")) {
	                	valor = getValor(buffer);
	                	if (categoria == INST)
	                   	 	addiCiclos = valor; //QUANTIDADE DE CICLOS DA ADDI
							ciclosParaExecutar[1]=addiCiclos;
	            	}
	            	else if (strstr(buffer, "add")) {
	                	valor = getValor(buffer);
	                	if (categoria == UF)
	                    	qtdeAdd = valor; //QUANTIDADE DE UF ADD
	                	else if (categoria == INST)
	                    	addCiclos = valor; //QUANTIDADE DE CICLOS DA ADD
							ciclosParaExecutar[0]=addCiclos;
	            	} 
					else if (strstr(buffer, "mul")) {
	                	valor = getValor(buffer);
	                	if (categoria == UF)
	                    	qtdeMul = valor; //QUANTIDADE DE UF MUL
	                	else if (categoria == INST)
	                    	mulCiclos = valor; //QUANTIDADE DE CICLOS DA MUL
							ciclosParaExecutar[4]=mulCiclos;
	            	} 
					else if (strstr(buffer, "int")) {
	                	valor = getValor(buffer);
	                	if (categoria == UF)
	                   	 	qtdeInt = valor; //QUANTIDADE DE UF INTEGER
	            	}
	            	else if (strstr(buffer, "div")) {
	                	valor = getValor(buffer);
	                	if (categoria == INST)
	                   	 	divCiclos = valor; //QUANTIDADE DE CICLOS DA DIV
							ciclosParaExecutar[5]=mulCiclos;
	            	}
	            	else if (strstr(buffer, "subi")) {
	                	valor = getValor(buffer);
	                	if (categoria == INST)
	                   	 	subiCiclos = valor; //QUANTIDADE DE CICLOS DA SUBI
							ciclosParaExecutar[3]=subiCiclos;
	            	}
                    else if (strstr(buffer, "sub")) {
	                	valor = getValor(buffer);
	                	if (categoria == INST)
	                   	 	subCiclos = valor; //QUANTIDADE DE CICLOS DA SUB
							ciclosParaExecutar[2]=subCiclos;
	            	}
	            	else if (strstr(buffer, "lw")) {
	                	valor = getValor(buffer);
	                	if (categoria == INST)
	                   	 	lwCiclos = valor; //QUANTIDADE DE CICLOS DA LW
							ciclosParaExecutar[14]=lwCiclos;
	            	}
	            	else if (strstr(buffer, "sw")) {
	                	valor = getValor(buffer);
	                	if (categoria == INST)
	                   	 	swCiclos = valor; //QUANTIDADE DE CICLOS DA SW
							ciclosParaExecutar[15]=swCiclos;
	            	}
	            	else if (strstr(buffer, "beq")) {
	                	valor = getValor(buffer);
	                	if (categoria == INST)
	                   	 	beqCiclos = valor; //QUANTIDADE DE CICLOS DA BEQ
							ciclosParaExecutar[11]=beqCiclos;
	            	}
	            	else if (strstr(buffer, "bne")) {
	                	valor = getValor(buffer);
	                	if (categoria == INST)
	                   	 	bneCiclos = valor; //QUANTIDADE DE CICLOS DA BNE
							ciclosParaExecutar[12]=bneCiclos;
	            	}
	            	else if (strstr(buffer, "blt")) {
	                	valor = getValor(buffer);
	                	if (categoria == INST)
	                   	 	bltCiclos = valor; //QUANTIDADE DE CICLOS DA BLT
							ciclosParaExecutar[9]=bltCiclos;
	            	}
	            	else if (strstr(buffer, "bgt")) {
	                	valor = getValor(buffer);
	                	if (categoria == INST)
	                   	 	bgtCiclos = valor; //QUANTIDADE DE CICLOS DA BGT
							ciclosParaExecutar[10]=bgtCiclos;
	            	}
	            	else if (strstr(buffer, "j")) {
	                	valor = getValor(buffer);
	                	if (categoria == INST)
	                   	 	jCiclos = valor; //QUANTIDADE DE CICLOS DA J
							ciclosParaExecutar[13]=jCiclos;
	            	}
	            	else if (strstr(buffer, "and")) {
	                	valor = getValor(buffer);
	                	if (categoria == INST)
	                   	 	andCiclos = valor; //QUANTIDADE DE CICLOS DA AND
							ciclosParaExecutar[6]=andCiclos;
	            	}
	            	else if (strstr(buffer, "or")) {
	                	valor = getValor(buffer);
	                	if (categoria == INST)
	                   	 	orCiclos = valor; //QUANTIDADE DE CICLOS DA OR
							ciclosParaExecutar[7]=orCiclos;
	            	}
	            	else if (strstr(buffer, "not")) {
	                	valor = getValor(buffer);
	                	if (categoria == INST)
	                   	 	notCiclos = valor; //QUANTIDADE DE CICLOS DA NOT
							ciclosParaExecutar[8]=notCiclos;
	            	}
	            }
	            else if (categoria == DADOS){
					dado = strtol(buffer, &endptr, 10);
					if (*endptr != '\0' && *endptr != '\n') {
        				printf("Erro na conversão da string para long int.\n");
    				}
	            	insereMemoria(dado);
					pc = pc + 4;
				}
	            
            	else{
                    unsigned int inst;
            		if(categoria == PL){
            			inst = instrucaoParaBinario(buffer);
            			insereMemoria(inst);
						pc = pc+4;
						qtdeInsts++;
            		}
				}
				
		        
				//instrucao* inst;
				//inst = nova_instrucao(buffer); 
			}
		} 
		
		inicializaUFs(qtdeAdd, qtdeMul, qtdeInt);
	    // Fecha o arquivo
	    fclose(arquivo);
        printMemoria();
		if((memsize-100)<qtdeInsts*4){
			printf("\nERRO: Não há espaço na memória para todas as instruções do programa.\n");
			return 0;
		}
	    // Imprime os valores lidos
	    printf("\n\nUFs - add: %d, mul: %d, int: %d\n\n", qtdeAdd, qtdeMul, qtdeInt);
	    printf("Ciclos de clock necessarios\npara completar a execucao:\nadd: %d, mul: %d, lw: %d\n", addCiclos, mulCiclos, lwCiclos);
        printf("div: %d, and: %d, addi: %d\nsubi: %d, or: %d, not: %d\n", divCiclos, andCiclos, addiCiclos, subiCiclos, orCiclos, notCiclos);
        printf("bgt: %d, blt: %d, beq: %d\nbne: %d, j: %d, sw: %d, sub: %d\n", bgtCiclos, bltCiclos, beqCiclos, bneCiclos, jCiclos, swCiclos, subCiclos);
		//inicializaPipeline();
		printRegistradores();

	if(output!=NULL){
		FILE *arq;
   		//printf("Escrevendo os resultados no arquivo %s.txt\n", output);
		arq = fopen(output,"w+");
	}
	return 1;
}
