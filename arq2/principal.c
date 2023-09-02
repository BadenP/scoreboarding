#include <stdlib.h>
#include <stdio.h>
#include "main.h"
#include <string.h>


int main(int argc, char *argv[]){

	if((strcmp(argv[1], "-p") == 0) && (strcmp(argv[3], "-m") == 0)){
        leituraArquivo(argv[2],atoi(argv[4]),argv[6]);
    }
    else{
        printf("Erro ao executar o programa.\n");
    }

  return 0;
}