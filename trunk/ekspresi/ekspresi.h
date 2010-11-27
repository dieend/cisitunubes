#ifndef ekspresi_H
#define ekspresi_H

#define MAXTOKEN 50
#define MAXSTACK 200
#include "../command/command.h"
#define ERROR "ERROR IN FUNCTION"
#define VERROR "ERROR IN VALUE"


#define lastToken(e) (e).token[(e).length]

typedef struct {
	char token[MAXTOKEN][MAXSTRINGLENGTH];
	int length;
	boolean error;
} ekspresi;

extern int countStack;

char * getInBracket(char raw[]);

ekspresi DoEkspresi(ekspresi Ekspresi);

ekspresi makeEkspresi(char rawEkspresi[]);
ekspresi makeIF(char rawEkspresi[]);

void tulisEkspresi(ekspresi Ekspresi);

#include "fungsi/dodo.h"
#endif
