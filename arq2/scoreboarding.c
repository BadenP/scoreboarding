#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


//Função para extrair o valor de UFs e quantidade de ciclos de execução
int extrair_valor(const char *linha) {
    char *separador = strstr(linha, ":");
    if (separador != NULL) {
        int valor;
        sscanf(separador + 1, "%d", &valor);
        return valor;
    }
    return 0; // Caso não encontre o separador, retorna 0.
}


void emissao(instrucao* inst){
	if (strcmp(inst->opcode,"add")==0){
		
	}

}

void leituraOperandos(){

}

void Execucao(){

}

void escritaResultados(){

}

void statusInstrucoes(){

}

void statusUFs(){

}

void statusRegistradores(){

}

/* void interpreta_instrucao(char *buffer){
	token = strtok(buffer, ", ");
	if (token == NULL) {
		printf("Erro: Opcode não encontrado.\n");
		continue;
	}
	*opcode = token;
	token = strtok(NULL, ", ");
	if (token == NULL) {
		printf("Erro: Argumento não encontrado.\n");
		continue;
	}
	arg1 = atoi(token);
	//memory[address++] = arg1;
	if (sscanf(token, "r%d", &x) == 1){
		arg1 = x;
		//memory[address++] = arg1;
	}		
	token = strtok(NULL, ", ");
	arg2 = atoi(token);
	if (sscanf(token, "r%d", &x) == 1){
		arg2 = x;
		//memory[address++] = arg2;
	}
	token = strtok(NULL, " \n");
	if (token == NULL){
		rg3 = 0;
	}
	else if (sscanf(token, "r%d", &x) == 1){
		arg3 = x;
		//memory[address++] = arg3;
	}
	else{
		arg3 = atoi(token);
		//memory[address++] = arg3;
	}
	
	exececutar_instrucao(*opcode, arg1, arg2, arg3);
	printRegist(regist);
	printGenReg();
} */

/*
void executar_instrucao(char opcode[4], int arg1, int arg2, int arg3) {
    if (strcmp(opcode, "add") == 0) {
        regist[arg1] = regist[arg2] + regist[arg3];
    } 
	else if (strcmp(opcode, "addi") == 0) {
		printf("%d %d %d", arg1, arg2, arg3);
        regist[arg1] = regist[arg2] + arg3;
    } 
	else if (strcmp(opcode, "sub") == 0) {
        regist[arg1] = regist[arg2] - regist[arg3];
    } 
	else if (strcmp(opcode, "subi") == 0) {
        regist[arg1] = regist[arg2] - arg3;
    } 
	else if (strcmp(opcode, "mul") == 0) {
        regist[arg1] = regist[arg2] * regist[arg3];
    } 
	else if (strcmp(opcode, "div") == 0) {
        regist[arg1] = regist[arg2] / regist[arg3];
    } 
	else if (strcmp(opcode, "bgt") == 0) {
        if (regist[arg2] > regist[arg1]) {
            pc = arg3;
        }
    } 
	else if (strcmp(opcode, "blt") == 0) {
        if (regist[arg2] < regist[arg1]) {
            pc = arg3;
        }
    } 
    else if (strcmp(opcode, "beq") == 0) {
        if (regist[arg2] == regist[arg1]) {
            pc = arg3;
        }
    } 
	else if (strcmp(opcode, "lw") == 0) {
        regist[arg1] = memory[regist[arg2]+arg2];
    } 
	else if (strcmp(opcode, "sw") == 0) {
        memory[regist[arg1]+arg3] = regist[arg2];
    } 
	else if (strcmp(opcode, "mov") == 0) {
        regist[arg1] = regist[arg2];
    } 
	else if (strcmp(opcode, "movi") == 0) {
        regist[arg1] = arg2;
    } 
	else {
        printf("Instrucao invalida: %s\n", opcode);
        exit(1);
    }
}
*/

int main(int argc, char *argv[]){

	if(argc == 3 && (strcmp(argv[1], "-p") == 0)){
		FILE *arquivo;
	    char buffer[100];
	    int instadd = 0, instmul = 0, instinti = 0;
		int qtdeAdd = 0, qtdeMul = 0, qtdeInt = 0;


	    // Abre o arquivo em modo de leitura
	    arquivo = fopen(argv[2], "r");
	
	    if (arquivo == NULL) {
	        printf("Erro ao abrir o arquivo.\n");
	        return 1;
	    }
	    
	    while (fgets(buffer, sizeof(buffer), arquivo)) {
	    	// printf("%s", &linha);
	        // Verifica se a linha contém a palavra-chave "UF"
	        if (strcmp(buffer, "UF\n") == 0) {
	            // Lê as próximas três linhas contendo os valores
	            fgets(buffer, sizeof(buffer), arquivo);
	            qtdeAdd = extrair_valor(buffer);
	
	            fgets(buffer, sizeof(buffer), arquivo);
	            qtdeMul = extrair_valor(buffer);
	
	            fgets(buffer, sizeof(buffer), arquivo);
	            qtdeInt = extrair_valor(buffer);
	        }
	
	        // Verifica se a linha contém a palavra-chave "INST"
	        if (strcmp(buffer, "INST\n") == 0) {
	            // Lê as próximas três linhas contendo os valores
	            fgets(buffer, sizeof(buffer), arquivo);
	            instadd = extrair_valor(buffer);
	
	            fgets(buffer, sizeof(buffer), arquivo);
	            instmul = extrair_valor(buffer);
	
	            fgets(buffer, sizeof(buffer), arquivo);
	            instinti = extrair_valor(buffer);
	        }
	       /* 
	        else{
	        	interpreta_instrucao(buffer);	        
			}*/
    	}

	
	    // Fecha o arquivo
	    fclose(arquivo);
	
	    // Imprime os valores lidos
	    printf("\nUFs - add: %d, mul: %d, int: %d\n\n", qtdeAdd, qtdeMul, qtdeInt);
	    printf("Ciclos de clock necessarios\npara completar a execucao:\nadd: %d, mul: %d, int: %d\n", instadd, instmul, instinti);
	
		//Inicializa UF's 
		UF *ufAdd = malloc(qtdeAdd * sizeof(UF));
		UF *ufMul = malloc(qtdeMul * sizeof(UF));
		UF *ufInt = malloc(qtdeInt * sizeof(UF));
		

		if(argc == 5 && (strcmp(argv[3], "-o") == 0)){
			FILE *arq;
			printf("Escrevendo os resultados no arquivo %s.txt\n", argv[4]);
			arq = fopen(argv[4],"w+");
		}

	    return 0;
	}
	else{
		printf("Erro na execução do programa. Tente novamente com o formato: ");
	}

  return 0;
}
