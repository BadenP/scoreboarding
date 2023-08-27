#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX 100

typedef enum { ADD, MUL, INT } tipoUF;
typedef enum { E, LO, EX, ER } estagiosPipeline;

typedef struct UF{
    tipoUF tipo;
	bool busy;
	char* operacao;
	char* fi;
	char* fj;
	char* fk;
	struct UF* qj;
	struct UF* qk;
	bool rj;
	bool rk;
}UF;

typedef struct instrucao {
    char *opcode;                   // Código da instrução (1: ADD, 2: MUL, 3: INT)
    int dest_reg;                   // Registrador de destino
    int operador1;                  // Registrador fonte 1
    int operador2;                  // Registrador fonte 2
    UF* uf;                         // Unidade Funcional associada à instrução
    int ciclos;                     // Ciclos de execução da instrução
    estagiosPipeline estagioAtual;  // Ciclos restantes para a conclusão da instrução
} instrucao;

typedef struct Registrador{
    char* nome, *valor;
}registrador;

typedef struct statusRegistrador{
    registrador* reg;
    UF * uf;
}statusReg;

typedef struct Scoreboarding{
    statusReg statusRegistradores;
    instrucao* memoriaInstrucoes;
    char statusInstrucoes[5][MAX];
}sb;

bool waw(instrucao primeira, instrucao segunda){
    if (primeira.dest_reg==segunda.dest_reg)
        return true;
    else
        false;
}

bool raw(instrucao primeira, instrucao segunda){
    if (primeira.dest_reg==segunda.operador1 || primeira.dest_reg==segunda.operador2)
        return true;
    else
        false;
}

bool war(instrucao primeira, instrucao segunda){
    if (segunda.dest_reg==primeira.operador1 || segunda.dest_reg==primeira.operador2)
        return true;
    else
        false;
}

const char* tipoToString(tipoUF tipo) {
    switch (tipo) {
        case ADD:
            return "ADD";
        case MUL:
            return "MUL";
        case INT:
            return "INT";
    }
}

void inicializa(int p[], UF** ufs){

    int qtdeUF = p[0]+p[1]+p[2];
    *ufs = (UF*)calloc(qtdeUF, sizeof(UF));

     for (int i = 0; i < qtdeUF; i++){
        if (i < p[0])
            (*ufs)[i].tipo = ADD;
        else if (i < p[0] + p[1])
            (*ufs)[i].tipo = MUL;
        else
            (*ufs)[i].tipo = INT;
    }

}

void printUFS(UF* ufs, int qtde){

    printf("UF  Tipo  Busy   Operacao   Fi      Fj      Fk       Qj       Qk     Rj     Rk\n");
    for (int i = 0; i < qtde; i++) {
        printf("%-4d %-4s %-7s %-7s %-7s %-7s %-7s %-6p %-6p %-6s %-7s\n",
               i, tipoToString(ufs[i].tipo), ufs[i].busy ? "true" : "false", ufs[i].operacao,
               ufs[i].fi, ufs[i].fj, ufs[i].fk, ufs[i].qj, ufs[i].qk,
               ufs[i].rj ? "true" : "false", ufs[i].rk ? "true" : "false");
    }
}




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

int main(int argc, char *argv[]){

	if(argc == 3 && (strcmp(argv[1], "-p") == 0)){
		FILE *arquivo;
	    char buffer[100];
        int parametrosUF[6];

	    // Abre o arquivo em modo de leitura
	    arquivo = fopen(argv[2], "r");
	
	    if (arquivo == NULL) {
	        printf("Erro ao abrir o arquivo.\n");
	        return 1;
	    }
	    
	    while (fgets(buffer, sizeof(buffer), arquivo)) {

	        // Verifica se a linha contém a palavra-chave "UF"
	        if (strcmp(buffer, "UF\n") == 0) {
	            // Lê as próximas três linhas contendo os valores
	            fgets(buffer, sizeof(buffer), arquivo);
	            parametrosUF[0] = extrair_valor(buffer);
	            fgets(buffer, sizeof(buffer), arquivo);
	            parametrosUF[1] = extrair_valor(buffer);
	            fgets(buffer, sizeof(buffer), arquivo);
	            parametrosUF[2] = extrair_valor(buffer);
	        }
	
	        // Verifica se a linha contém a palavra-chave "INST"
	        if (strcmp(buffer, "INST\n") == 0) {
	            // Lê as próximas três linhas contendo os valores
	            fgets(buffer, sizeof(buffer), arquivo);
	            parametrosUF[3] = extrair_valor(buffer);
	            fgets(buffer, sizeof(buffer), arquivo);
	            parametrosUF[4] = extrair_valor(buffer);
	            fgets(buffer, sizeof(buffer), arquivo);
	            parametrosUF[5] = extrair_valor(buffer);
	        }
	       /* 
	        else{
	        	interpreta_instrucao(buffer);	        
			}*/
    	}

	    // Fecha o arquivo
	    fclose(arquivo);
	
	    // Imprime os valores lidos
	    printf("\nUFs - add: %d, mul: %d, int: %d\n\n", parametrosUF[0],parametrosUF[1],parametrosUF[2]);
	    printf("Ciclos de clock necessarios\npara completar a execucao:\nadd: %d, mul: %d, int: %d\n", parametrosUF[3],parametrosUF[4],parametrosUF[5]);
	
		//Inicialização 
        sb scoreboarding;
        UF * ufs;
        registrador* regs;
        inicializa(parametrosUF, &ufs);
        printUFS(ufs,parametrosUF[0]+parametrosUF[1]+parametrosUF[2]);
		free(ufs);

		/* if(argc == 5 && (strcmp(argv[3], "-o") == 0)){
			FILE *arq;
			printf("Escrevendo os resultados no arquivo %s.txt\n", argv[4]);
			arq = fopen(argv[4],"w+");
		} */
	    
	}
	else{
		printf("Erro na execução do programa. Tente novamente com o formato: ");
	}

    return 0;
}
