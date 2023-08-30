#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX 100
int pc=0;

typedef enum { ADD, MUL, INT } tipoUF;
typedef enum { E, LO, EX, ER } estagiosPipeline;

unsigned int *memoria;
unsigned int bancoRegs[32];

void insereMemoria(unsigned int instrucao){
    if(memoria==NULL){
        printf("Erro.");
    }
    else{
        memoria[pc]=instrucao;
    }
}

void inicializaMemoria(int m){
    memoria = (unsigned int*)malloc(sizeof(unsigned int) * m);
    if (memoria == NULL) {
        printf("Erro ao alocar memória.\n");
        exit(1); 
    }
}

void imprimeMemoria(int m) {
    printf("Conteúdo da memória:\n");
    for (int i = 0; i < m; i++) {
        printf("Endereço %d: %u\n", i, memoria[i]);
    }
}


typedef struct UF{
    tipoUF tipo;
	bool busy;
	unsigned int operacao;
	unsigned int fi;
	unsigned int fj;
	unsigned int fk;
	struct UF* qj;
	struct UF* qk;
	bool rj;
	bool rk;
    int qtde_ciclos;
}UF;

typedef struct{
    UF * ufAdd;
    UF * ufMul;
    UF * ufInt;
}conjuntoUFS;

typedef struct {
    unsigned int busca;
    unsigned int emissao;
    unsigned int leitura_op;
    conjuntoUFS execucao;
    unsigned int escrita;
}pipeline;

typedef struct instrucao {
    unsigned int opcode;            // Código da instrução (1: ADD, 2: MUL, 3: INT)                  // Registrador de destino
    unsigned int dest_reg, operador1, operador2;                  // Registrador fonte 2
    UF* uf;                         // Unidade Funcional associada à instrução
    int ciclosExecucao, ciclosAtuais;                     // Ciclos de execução da instrução
    estagiosPipeline estagioAtual;  // Ciclos restantes para a conclusão da instrução
} instrucao;


void inicializaUFS(int p[], UF** ufs){

    int qtdeUF = p[0]+p[1]+p[2];
    *ufs = (UF*)malloc(qtdeUF * sizeof(UF));

     for (int i = 0; i < qtdeUF; i++){
        if (i < p[0])
            (*ufs)[i].tipo = ADD;
        else if (i < p[0] + p[1])
            (*ufs)[i].tipo = MUL;
        else
            (*ufs)[i].tipo = INT;
    }

    //ufs[0] representa as unidades funcionais de add

    //ufs[1] representa as unidades funcionais de mul

    //ufs[2] representa as unidades funcionais de sub


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


void printUF(UF* uf) {
    printf("Tipo: %d\n", uf->tipo);
    printf("Busy: %d\n", uf->busy);
    printf("Tipo: %d\n", uf->tipo);
    printf("Busy: %d\n", uf->busy);
    printf("Tipo: %d\n", uf->tipo);
    printf("Busy: %d\n", uf->busy);
    printf("Tipo: %d\n", uf->tipo);
    printf("Busy: %d\n", uf->busy);
    printf("Tipo: %d\n", uf->tipo);
    printf("Busy: %d\n", uf->busy);
    // Print other UF fields
    // ...
}

void printConjuntoUFS(conjuntoUFS* conjunto) {
    printf("UF Add:\n");
    printUF(conjunto->ufAdd);
    
    printf("UF Mul:\n");
    printUF(conjunto->ufMul);
    
    printf("UF Int:\n");
    printUF(conjunto->ufInt);
}

void printPipeline(pipeline* pipe) {
    printf("Busca: %u\n", pipe->busca);
    printf("Emissao: %u\n", pipe->emissao);
    printf("Leitura OP: %u\n", pipe->leitura_op);
    printf("Execução:\n");
    printConjuntoUFS(&(pipe->execucao));
    printf("Escrita: %u\n", pipe->escrita);
}


void printUFS(UF* ufs, int qtde){

    printf("UF  Tipo  Busy   Operacao   Fi      Fj      Fk       Qj       Qk     Rj     Rk\n");
    for (int i = 0; i < qtde; i++) {
        printf("%-4d %-4s %-7s %-7u %-7u %-7u %-7u %-6p %-6p %-6s %-7s\n",
               i, tipoToString(ufs[i].tipo), ufs[i].busy ? "true" : "false", ufs[i].operacao,
               ufs[i].fi, ufs[i].fj, ufs[i].fk, ufs[i].qj, ufs[i].qk,
               ufs[i].rj ? "true" : "false", ufs[i].rk ? "true" : "false");
    }
}

void printMemoria(int m){

    for(int i=0; i<m; i++){
        printf("\n%u",memoria[i]);
    }
}

pipeline pipe;

void inicializaPipeline(int add, int mul, int inteiro){

    pipe.execucao.ufAdd=(UF*)malloc(sizeof(UF*)*add);
    pipe.execucao.ufInt=(UF*)malloc(sizeof(UF*)*mul);
    pipe.execucao.ufMul=(UF*)malloc(sizeof(UF*)*inteiro);
    pipe.execucao.ufAdd->tipo=0;
    pipe.execucao.ufMul->tipo=1;
    pipe.execucao.ufInt->tipo=2;

}

unsigned int get(unsigned int instrucao){

    int mascara=63;
    int codOpcode=mascara&instrucao;
 
    if(codOpcode<9 && (codOpcode!=1 && codOpcode !=3)){

        //Caso NOT
        if (codOpcode == 8){
            char* arg1,*arg2;
            arg1 = strtok(NULL, "r ,");
            arg2 = strtok(NULL, "r \r\n");
            printf("\n%s ", token);
            rd=atoi(arg1);
            printf("%s ", arg1);
            rs=atoi(arg2);
            printf("%s ", arg2);
            rs = rs << 21;
            inst = inst | rs;
            rd = rd << 11;
            inst = inst | rd;
        }
        else{
            char* arg1,*arg2,*arg3;
            arg1 = strtok(NULL, "r ,");
            arg2 = strtok(NULL, "r ,");
            arg3 = strtok(NULL, "r \r\n");
            printf("\n%s ", token);
            rs=atoi(arg1);
            printf("%s ", arg1);
            rt=atoi(arg2);
            printf("%s ", arg2);
            rd=atoi(arg3);
            printf("%s ", arg3);
            rs = rs << 21;
            inst = inst | rs;
            rt = rt << 16;
            inst = inst | rt;
            rd = rd << 11;
            inst = inst | rd;
        }
    }
    else if(codOpcode==16 || codOpcode==13){
        if(codOpcode == 13){
            char* arg1;
            arg1 = strtok(NULL, " \r\n");
            address = atoi(arg1);
            printf("\n%s ", token);
            printf("%s ", arg1);
            address = address << 0;
            inst = inst | address;
        }
        else{
            printf("\n%s ", token); //Caso do exit 
        }
    }
    else{
        char* arg1,*arg2,*arg3;
        if(codOpcode==14 || codOpcode==15){
            arg1 = strtok(NULL, "r ,");
            arg2 = strtok(NULL, " (");
            arg3 = strtok(NULL, "r )\r\n");
            printf("\n%s ", token);
            rs=atoi(arg3);
            printf("%s ", arg3);
            rt=atoi(arg1);
            printf("%s ", arg1);
            imm=atoi(arg2);
            printf("%s ", arg2);
        }
        else{
            arg1 = strtok(NULL, "r ,");
            arg2 = strtok(NULL, "r ,");
            arg3 = strtok(NULL, ", \r\n");
            printf("\n%s ", token);
            rs=atoi(arg1);
            printf("%s ", arg1);
            rt=atoi(arg2);
            printf("%s ", arg2);
            imm=atoi(arg3);
            printf("%s ", arg3);
        }

        rs = rs << 21;
        inst = inst | rs;
        rt = rt << 16;
        inst = inst | rt;
        imm = imm << 0;
        inst = inst | imm;

    }

    printf("%u",inst);
    return inst;


} 

unsigned int getOpcode(unsigned int instrucao){
    unsigned int mascara=63;
    unsigned int codOpcode=mascara&instrucao;    
    return codOpcode;
} 

unsigned int getRegistradorDestino(unsigned int instrucao){
    unsigned int mascara=63;
    unsigned int codOpcode=mascara&instrucao;    
    return codOpcode;    
} 

unsigned int getRegistradorDestino(unsigned int instrucao){
    unsigned int mascara=63;
    unsigned int codOpcode=mascara&instrucao;    
    return codOpcode;    
} 


int main(int argc, char *argv[]){

    int m=100;
    int qtdeAdd = 2;
    int qtdeMul = 3;
    int qtdeInt = 1;
    unsigned int exemploPrograma[10]={50,100,150,200,250,300,350,400,450,500};

    //leitura do programa FEITO

    //fase de inicializacao FEITA
    /* A memória tem que ser inicializada
        As UFS tem que ser inicializadas
        Banco de registradores
        Pipeline
    
    */
    //Tem que inicializar o banco com os dados obtidos em .dados
    inicializaPipeline(qtdeAdd,qtdeMul,qtdeInt);
    inicializaMemoria(m);

    //printUFS(pipe->execucao,8);
    imprimeMemoria(m);

    //carrega o programa para a memoria
    for (int i=0; i<sizeof(exemploPrograma)/sizeof(exemploPrograma[0]); i++){
        insereMemoria(exemploPrograma[i]);
        pc++;
    }

    imprimeMemoria(m);

    //começa a execução do pipeline
     while(getOpcode(pipe.busca)!=16){
        if(pipe.escrita!=0){
            //efetivar pipe.escrita
        }
        pipe.escrita=0;
        
        //VERIFICAR WAR 
        for (int i=0; i<; i++){
            if(pipe.execucao.ufAdd[i].qtde_ciclos==0){
                pipe.escrita=//instrucao obtida de pipe.execucao.ufAdd[i]
            }
        }

        for (int i=0; i<; i++){
            if(pipe.execucao.ufMul[i].qtde_ciclos==0){
                pipe.escrita=//instrucao obtida de pipe.execucao.ufAdd[i]
            }
        }

        for (int i=0; i<; i++){
            if(pipe.execucao.ufInt[i].qtde_ciclos==0){
                pipe.escrita=//instrucao obtida de pipe.execucao.ufAdd[i]
            }
        }

        //tira a intrucao finalizada da UF, ou seja, deixa a UF BUSY=FALSE e reinicia? a UF

        if(//se tem UF livre){
            pipe.leitura_op=0;
            //enfia na execucao
        }
        else{
            //deixa a instrucao lá, ou seja, pipe.leitura_op!=0
        }

        if(//pipe.leitura_op==0 AND //verifica war){

            //manda p pipe.leitura_op
        }
        else{
            //continua do jeito q ta 
        }

        if(WAW){
            //nao emite
            //nao busca a proxima
        }
        else{
            //emite
            //busca a proxima
            pipe.busca=memoria[pc];
        }
        
        pc++;
        clock++;

    } 




    //fim
    free(memoria);





}