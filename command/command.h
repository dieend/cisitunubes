#ifndef command_H
#define command_H
#include "boolean.h"
#include <stdio.h>
#include <stdlib.h>
#define DEBUG puts("OK")
#define MAXPARAM 5
#include "../kata/kata.h"
typedef struct {
	char param[MAXPARAM][MAXSTRINGLENGTH];
	int length;
} command;
#include "../worksheet/worksheet.h"
#include "../files/files.h"
#include "../directory/directory.h"
#include "../ekspresi/ekspresi.h"


void clean(command * Command);
/* Inisiasi Command menjadi kosong */

command readCommand();
/* Memparsing input menjadi Command dengan argumen-argumennya */

int processCommandDocument(command Command);
/* Memproses Command untuk modus Document */

int processCommandFile(command Command);
/* Memproses Command untuk modus File */


#endif
