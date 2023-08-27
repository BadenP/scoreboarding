#ifndef BARRAMENTO_H_
#define BARRAMENTO_H_

	#include <stdio.h>
	#include <string.h>
	#include <stdlib.h>

	#include "memoria.h"

	extern unsigned char barramento[4];

	void JogaNoBarramento(unsigned char*);
	unsigned char* PegaNoBarramento();

#endif