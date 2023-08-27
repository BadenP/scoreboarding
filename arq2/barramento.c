#include <stdio.h>
#include <stdlib.h>
#include "memoria.h"

#include "tradutor.h"
#include "common.h"

#include "barramento.h"

unsigned char barramento[4];

void insereBarramento(unsigned char *value){
	barramento[0] = value[0];
	barramento[1] = value[1];
	barramento[2] = value[2];
	barramento[3] = value[3];
}

unsigned char* fetchBarramento(){
	return (barramento);
}