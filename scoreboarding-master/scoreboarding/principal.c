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
        char* output = NULL;
        int largura = 3;
        //Esta função lê o programa e o carrega para a memória
        //Memória é inicializada 
        //Banco de registradores é inicializado
        //UFS são inicializadas
        //Status das instruções é inicializado
        //Qtde de ciclos para executar de cada instrução são salvas em um vetor
        if(argv[5]!=NULL){
          if(strcmp(argv[5], "-o")==0){
            output = argv[6];
          }
          else if(strcmp(argv[5], "-l")==0){
            largura = atoi(argv[6]);
          }
        }
        if(argv[7]!=NULL){
          if(strcmp(argv[7], "-o")==0){
            output = argv[8];
          }
          else if(strcmp(argv[7], "-l")==0){
            largura = atoi(argv[8]);
          }
        }
        if(!leituraArquivo(argv[2],atoi(argv[4]),output, largura)){
          printf("Modo correto de uso: './programa -p <arquivo_entrada.sb> -m <tamanho_memoria> [-o <arquivo_saida>] [-l <largura_escrita>]'\n");
          return 0;
        }
        int programaPersiste = 1;
        pc = 400;
        clocki = 1;
        stalled = 0;
        int cont;
        if(arq_saida){
          do{
            //printf("\n--------CICLO %d--------\nPressione enter para continuar\n", clocki);
            escritaResultados();
            execucao();
            leituraDeOperandos();
            emiteInstrucao();
            cont = buscaInstrucao();
            printf("\nPC = %d\nIR = %d", pc, ir);
            clocki++;
            printStatusInstrucoes();
            statusUFs();
            printStatusReg();
            //printRegistradores();
            //printMemoria();
            //printBarramentoResultados();
          }while((instrucoesEmitidas == 0 || instrucoesEmitidas!=instrucoesEfetivadas) || cont);
        }
        else{
          do{
            //printf("\n--------CICLO %d--------\nPressione enter para continuar\n", clocki);
            escritaResultados();
            execucao();
            leituraDeOperandos();
            emiteInstrucao();
            cont = buscaInstrucao();
            printf("\nPC = %d\nIR = %d", pc, ir);
            clocki++;
            printStatusInstrucoes();
            statusUFs();
            printStatusReg();
            //printRegistradores();
            //printMemoria();
            //printBarramentoResultados();
            while (getchar() != '\n') {
            }
          }while((instrucoesEmitidas == 0 || instrucoesEmitidas!=instrucoesEfetivadas) || cont);
        }
        printf("\n\nFIM DO PROGRAMA\n");
        printRegistradores();
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
  free(barramentoResultados);
  //fclose(arq_saida);
  return 0;
}