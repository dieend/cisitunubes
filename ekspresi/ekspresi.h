#ifndef ekspresi_H
#define ekspresi_H

#define MAXTOKEN 50
#include "../command/command.h"

typedef struct {
	char token[MAXTOKEN][MAXSTRINGLENGTH];
	int length;
} ekspresi;

void makeEkspresi(ekspresi * Ekspresi,char rawEkspresi[]);

#endif
