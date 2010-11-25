#ifndef kata_H
#define kata_H
#include "../command/boolean.h"
#define MAXSTRINGLENGTH 50
int sstrlen(char kata[]);
void sstrcat(char kata1[], char kata2[]);
void sstrcpy(char kata1[], char kata2[]);
int sstrcmp(char kata1[], char kata2[]);
boolean isSubString(char kata1[], char kata2[]);

#endif
