#ifndef MAIN_H
#define MAIN_H

extern int ciclosParaExecutar[16];
extern int clock;
extern int qtdeAdd, qtdeInt, qtdeMul;
extern int addCiclos, mulCiclos, lwCiclos, subCiclos, divCiclos, swCiclos, bgtCiclos, jCiclos;
extern int addiCiclos, subiCiclos, andCiclos, orCiclos, notCiclos, bltCiclos, beqCiclos, bneCiclos;
int getValor(const char *linha);
int leituraArquivo(char * file, int memsize, char * output);
#endif
