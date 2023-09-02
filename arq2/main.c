#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tradutor.h"
#include "memoria.h"
#include "registradores.h"
#include "main.h"

int getValor(const char *linha) {
    char *separador = strstr(linha, ":");
    if (separador != NULL) {
        int valor;
        sscanf(separador + 1, "%d", &valor);
        return valor;
    }
    return 0; // Caso não encontre o separador, retorna 0.
}

void leituraArquivo(char * file, int memsize, char * output){

		FILE *arquivo;
	    char buffer[256];
	    int ufadd, ufinti, ufmul;
	    int addCiclos = 0, mulCiclos = 0, lwCiclos = 0, subCiclos=0, divCiclos=0, swCiclos=0, bgtCiclos = 0, jCiclos = 0;
	    int addiCiclos = 0, subiCiclos = 0, andCiclos = 0, orCiclos = 0, notCiclos = 0, bltCiclos = 0, beqCiclos=0, bneCiclos=0;
	    // Abre o arquivo em modo de leitura
	    arquivo = fopen(file, "r");
	    //int memsize = atoi(argv[4]);
        inicializaMemoria(memsize);
	
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
	            	}
	            	else if (strstr(buffer, "add")) {
	                	valor = getValor(buffer);
	                	if (categoria == UF)
	                    	ufadd = valor; //QUANTIDADE DE UF ADD
	                	else if (categoria == INST)
	                    	addCiclos = valor; //QUANTIDADE DE CICLOS DA ADD
	            	} 
					else if (strstr(buffer, "mul")) {
	                	valor = getValor(buffer);
	                	if (categoria == UF)
	                    	ufmul = valor; //QUANTIDADE DE UF MUL
	                	else if (categoria == INST)
	                    	mulCiclos = valor; //QUANTIDADE DE CICLOS DA MUL
	            	} 
					else if (strstr(buffer, "int")) {
	                	valor = getValor(buffer);
	                	if (categoria == UF)
	                   	 	ufinti = valor; //QUANTIDADE DE UF INTEGER
	            	}
	            	else if (strstr(buffer, "div")) {
	                	valor = getValor(buffer);
	                	if (categoria == INST)
	                   	 	divCiclos = valor; //QUANTIDADE DE CICLOS DA DIV
	            	}
	            	else if (strstr(buffer, "subi")) {
	                	valor = getValor(buffer);
	                	if (categoria == INST)
	                   	 	subiCiclos = valor; //QUANTIDADE DE CICLOS DA SUBI
	            	}
                    else if (strstr(buffer, "sub")) {
	                	valor = getValor(buffer);
	                	if (categoria == INST)
	                   	 	subCiclos = valor; //QUANTIDADE DE CICLOS DA SUBI
	            	}
	            	else if (strstr(buffer, "lw")) {
	                	valor = getValor(buffer);
	                	if (categoria == INST)
	                   	 	lwCiclos = valor; //QUANTIDADE DE CICLOS DA LW
	            	}
	            	else if (strstr(buffer, "sw")) {
	                	valor = getValor(buffer);
	                	if (categoria == INST)
	                   	 	swCiclos = valor; //QUANTIDADE DE CICLOS DA SW
	            	}
	            	else if (strstr(buffer, "beq")) {
	                	valor = getValor(buffer);
	                	if (categoria == INST)
	                   	 	beqCiclos = valor; //QUANTIDADE DE CICLOS DA BEQ
	            	}
	            	else if (strstr(buffer, "bne")) {
	                	valor = getValor(buffer);
	                	if (categoria == INST)
	                   	 	bneCiclos = valor; //QUANTIDADE DE CICLOS DA BNE
	            	}
	            	else if (strstr(buffer, "blt")) {
	                	valor = getValor(buffer);
	                	if (categoria == INST)
	                   	 	bltCiclos = valor; //QUANTIDADE DE CICLOS DA BLT
	            	}
	            	else if (strstr(buffer, "bgt")) {
	                	valor = getValor(buffer);
	                	if (categoria == INST)
	                   	 	bgtCiclos = valor; //QUANTIDADE DE CICLOS DA BGT
	            	}
	            	else if (strstr(buffer, "j")) {
	                	valor = getValor(buffer);
	                	if (categoria == INST)
	                   	 	jCiclos = valor; //QUANTIDADE DE CICLOS DA J
	            	}
	            	else if (strstr(buffer, "and")) {
	                	valor = getValor(buffer);
	                	if (categoria == INST)
	                   	 	andCiclos = valor; //QUANTIDADE DE CICLOS DA AND
	            	}
	            	else if (strstr(buffer, "or")) {
	                	valor = getValor(buffer);
	                	if (categoria == INST)
	                   	 	orCiclos = valor; //QUANTIDADE DE CICLOS DA OR
	            	}
	            	else if (strstr(buffer, "not")) {
	                	valor = getValor(buffer);
	                	if (categoria == INST)
	                   	 	notCiclos = valor; //QUANTIDADE DE CICLOS DA NOT
	            	}
	            }
	            else if (categoria == DADOS){
	            	printf("\nDADOS");
				}
	            
            	else{
                    unsigned int inst;
            		if(categoria == PL){
            			inst = instrucaoParaBinario(buffer);
            			insereMemoria(inst);
						pc++;
            		}
				}
				
		        
				//instrucao* inst;
				//inst = nova_instrucao(buffer); 
			}
		} 
		
	    // Fecha o arquivo
	    fclose(arquivo);
        printMemoria();
	    // Imprime os valores lidos
	    printf("\n\nUFs - add: %d, mul: %d, int: %d\n\n", ufadd, ufmul, ufinti);
	    printf("Ciclos de clock necessarios\npara completar a execucao:\nadd: %d, mul: %d, lw: %d\n", addCiclos, mulCiclos, lwCiclos);
        printf("div: %d, and: %d, addi: %d\nsubi: %d, or: %d, not: %d\n", divCiclos, andCiclos, addiCiclos, subiCiclos, orCiclos, notCiclos);
        printf("bgt: %d, blt: %d, beq: %d\nbne: %d, j: %d, sw: %d, sub: %d\n", bgtCiclos, bltCiclos, beqCiclos, bneCiclos, jCiclos, swCiclos, subCiclos);
	

	if(output!=NULL){
		FILE *arq;
   		printf("Escrevendo os resultados no arquivo %s.txt\n", output);
		arq = fopen(output,"w+");
	}

  
}