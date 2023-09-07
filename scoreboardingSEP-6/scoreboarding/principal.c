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
        int programaPersiste = 1;
        pc = 100;
        clocki = 1;
        stalled = 0;
        while(instrucoesEmitidas == 0 || instrucoesEmitidas!=instrucoesEfetivadas){
          printf("\n--------CICLO %d--------\nPressione enter para continuar\n", clocki);
          escritaResultados();
          execucao();
          leituraDeOperandos();
          emiteInstrucao();
          buscaInstrucao();
          printf("\nPC = %d\nIR = %d", pc, ir);
          clocki++;
          printStatusInstrucoes();
          printRegistradores();
          //printMemoria();
          //statusUFs();
          printf("\nBARRAMENTO RESULTS: %d", barramentoResultados);
          while (getchar() != '\n') {
          }
        }
        printf("\n\nFIM DO PROGRAMA\n");
        /*
        buscaInstrucao();
        clock++;
        emiteInstrucao();
        clock++;
        leituraDeOperandos();
        clock++;
        execucao();
        clock++;
        execucao();
        clock++;
        execucao();
        clock++;
        escritaResultados();
        */
        //statusUFs();
    }
    else{
        printf("Erro ao executar o programa.\n");
    }
  free(memoria);
  free(unidadesFuncionais.ufAdd);
  free(unidadesFuncionais.ufInt);
  free(unidadesFuncionais.ufMul);
  free(statusI);
  //free(unidadesFuncionais.ufMul);
  return 0;
}