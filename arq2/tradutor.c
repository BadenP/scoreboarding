#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memoria.h"
#include "tradutor.h"

int getCodigoOpcode(const char opcode[4]) {

    if (strcmp(opcode, "add") == 0) {
        return 0;
    } else if (strcmp(opcode, "addi") == 0) {
        return 1;
    } else if (strcmp(opcode, "sub") == 0) {
        return 2;
    } else if (strcmp(opcode, "subi") == 0) {
        return 3;
    } else if (strcmp(opcode, "mul") == 0) {
        return 4;
    } else if (strcmp(opcode, "div") == 0) {
        return 5;
    } else if (strcmp(opcode, "and") == 0) {
        return 6;
    } else if (strcmp(opcode, "or") == 0) {
        return 7;
    } else if (strcmp(opcode, "not") == 0) {
        return 8;
    } else if (strcmp(opcode, "blt") == 0) {
        return 9;
    } else if (strcmp(opcode, "bgt") == 0) {
        return 10;
    } else if (strcmp(opcode, "beq") == 0) {
        return 11;
    } else if (strcmp(opcode, "bne") == 0) {
        return 12;
    } else if (strcmp(opcode, "j") == 0) {
        return 13;
    } else if (strcmp(opcode, "lw") == 0) {
        return 14;
    } else if (strcmp(opcode, "sw") == 0) {
        return 15;
    } else if (strcmp(opcode, "exit") == 0) {
        return 16;
    } else {
        return -1;
    }
}


unsigned int instrucaoParaBinario(char *buffer){
    char* token;
    unsigned int inst=0;
    token = strtok(buffer, " ");
    unsigned int codOpcode = getCodigoOpcode(token);
    unsigned int rs, rd, rt, imm, address;
    inst = codOpcode << 26;

    if(codOpcode<9 && (codOpcode!=1 && codOpcode !=3)){
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
            printf("\n%s ", token);
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
        if(imm != abs(imm)){
        	int sinal = 1;
        	sinal = sinal << 15;
        	inst = inst | sinal;
		}	
        imm = abs(imm) << 0;
        inst = inst | imm;
    }

    printf("%u\n",inst);
    return inst;
}

void printBinario(unsigned int num) {
    int bits = sizeof(num) * 8;

    for (int i = bits - 1; i >= 26; i--) {
        unsigned int bit = (num >> i) & 1;
        printf("%u", bit);
    }
    printf("  ");

    for (int i = 25; i >= 21; i--) {
        unsigned int bit = (num >> i) & 1;
        printf("%u", bit);
    }
    printf("  ");

    for (int i = 20; i >= 16 ; i--) {
        unsigned int bit = (num >> i) & 1;
        printf("%u", bit);
    }
    printf("  ");

    for (int i = 15; i >= 11 ; i--) {
        unsigned int bit = (num >> i) & 1;
        printf("%u", bit);
    }
    printf("  ");

    for (int i = 10; i >= 0 ; i--) {
        unsigned int bit = (num >> i) & 1;
        printf("%u", bit);
    }

    printf("\n");
}
