#ifndef directory_H
#define directory_H

#include "../command/command.h"

typedef struct {
	char date[20][12];
	char hour[20][7];
	char size[20][20];
	char name[20][MAXSTRINGLENGTH];
	char sum[20];
	int all;
} directory;

extern directory Dir;
extern FILE * FXINT;

void transferDirectory();
/* Memparsing dari system("dir") menjadi variable Dir */

void Find(command Command);
/* Melaksanakan command Find */

void Open(command Command);
/* Melaksanakan command Open */

void New(command Command);
/* Membuat file baru dan open file tersebut */

void Delete(command Command);
/* Melaksanakan command Delete */

void Exit();

void searchName(char* Name);
void searchDate(char* Date);
void searchSize(char* Size);
void List();
/* Melaksanakan command list */

void makeNew(command Command);
#endif
