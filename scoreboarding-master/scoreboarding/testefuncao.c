#include <stdio.h>
#include <stdlib.h>


int main(){

    int destino = 33;
    int valor = 11931;
    int resultado = destino << 26;
    int endereco;

    if(valor!= abs(valor)){
        	int sinal = 1;
        	sinal = sinal << 25;
        	resultado = resultado | sinal;
		}	
        valor = abs(valor) << 0;
        resultado = resultado | valor;

    printf("resultado completo: %d\n\n",resultado);


    int mascara_destino = 0xFC000000; // 11111100000000000000000000000000 em binário
    // Extrai os 6 bits mais significativos (destino)
    int bits_destino = (resultado >> 26) & 0x3F;
    // Limpa os 6 bits mais significativos do resultado (obtendo o "resto")
    int resto = resultado & ~mascara_destino;

    if (bits_destino>=0 && bits_destino<=31){
        printf("INSERINDO %d em REGISTRADOR %d\n",resto,bits_destino);
        //bancoRegs[bits_destino]=resto;
    }
    else if(bits_destino==32){
        printf("INSERINDO em pc o valor %d\n",resto);
        int pc=resto;
    }
    else if(bits_destino==33){

        //ISSO AQUI NAO TA DANDO CERTO MAS TEM Q AJUSTAR Q DA CERTO O RESTO DA FUNSIONANDO

        if(destino==33){
        endereco = 8;
        endereco = endereco << 25;
        resto = resto | endereco;
            if(valor!= abs(valor)){
                int sinal = 1;
                sinal = sinal << 15;
                resto = resto | sinal;
            }	
            valor = abs(valor) << 0;
            resto = resto | valor;
    }
        // Extract bits 25 to 16 for the address
            printf("INSERINDO em memoria endereco %d o valor %d\n",endereco,resto);
    
        
    } 


    return 0;

}