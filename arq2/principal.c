#include <stdlib.h>
#include <stdio.h>
#include "main.h"
#include <string.h>


int main(int argc, char *argv[]){

	if((strcmp(argv[1], "-p") == 0) && (strcmp(argv[3], "-m") == 0)){

        //Esta função lê o programa e o carrega para a memória
        //Memória é inicializada 
        //Banco de registradores é inicializado
        //UFS são inicializadas
        //Qtde de ciclos para executar de cada instrução são salvas em um vetor
        leituraArquivo(argv[2],atoi(argv[4]),argv[6]);
    }
    else{
        printf("Erro ao executar o programa.\n");
    }

  return 0;
}