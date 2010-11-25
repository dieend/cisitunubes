#ifndef files_H
#define files_H

#include "../command/command.h"

#define ekstensi ".xcl"
extern char pathFile[MAXSTRINGLENGTH];
boolean adaKoma(char cek[]);
boolean angkaSemua(char cek[]);
void transferCell();
void doModusFile(char path[MAXSTRINGLENGTH]);
void Remove(command Command);
void Save();
void Write(command Command);
void Display(command Command);
void Evaluate(command Command);
#endif
