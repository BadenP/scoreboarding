#include <stdlib.h>
#include <stdio.h>
#include "main.h"
#include "processor.h"
#include <string.h>
#include "scoreboarding.h"


int main(int argc, char *argv[]){

	if((strcmp(argv[1], "-p") == 0) && (strcmp(argv[3], "-m") == 0)){
        if(atoi(argv[4])<101){
          printf("\nErro ao carregar memória: deve ser maior que 100\n");
          return 0;
        }
        //Esta função lê o programa e o carrega para a memória
        //Memória é inicializada 
        //Banco de registradores é inicializado
        //UFS são inicializadas
        //Status das instruções é inicializado
        //Qtde de ciclos para executar de cada instrução são salvas em um vetor
        if(!leituraArquivo(argv[2],atoi(argv[4]),argv[6])){
          return 0;
        }
        pc = 100;
        clock = 1;
        buscaInstrucao();
        clock++;
        emiteInstrucao();
        clock++;
        leituraDeOperandos();
        clock++;
        execucao();
        clock++;
        execucao();
        //statusUFs();
    }
    else{
        printf("Erro ao executar o programa.\n");
    }

  return 0;
}
