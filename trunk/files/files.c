#include "files.h"

char  pathFile[MAXSTRINGLENGTH];

boolean adaKoma(char cek[]) {
	int len = sstrlen(cek);
	int i;
	for (i=0; i<len; i++){
		if (cek[i] =='.') return true;
		if ('0' <= cek[i] && cek[i] <='9') continue;
		return false;
	}
	return false;
}

boolean angkaSemua(char cek[]) {
	int len = sstrlen(cek);
	int i;
	for (i=0; i<len; i++) {
		if (!('0' <= cek[i] && cek[i] <='9')) return false;
	}
	return true;
}



void transferCell(char path[]) {
	FILE * processedFile = fopen(path,"r");
	char kol[10],isi[MAXSTRINGLENGTH];
	int baris;
	addressCell Cell;
	fscanf(processedFile,"%s",kol);
	while (sstrcmp(kol,"#")) {
		fscanf(processedFile,"%d : %s",&baris,isi);
		Cell = getCell(baris,nomorKolom(kol));
		insert(Cell, isi);
		fscanf(processedFile,"%*s");
		fscanf(processedFile,"%s",kol);
	}
	fclose(processedFile);
}

void doModusFile(char path[]){
	alokasiWorksheet();
	sstrcpy(pathFile,path);
	transferCell(path);
	do{
		printf(">>");
	} while (processCommandFile(readCommand()));
}

void Remove(command Command){
	char tmp[MAXSTRINGLENGTH];
	area Area;
	Area = makeArea(tmp);
	makeEmpty(Area);
}


void Save() {
	FILE * processedFile = fopen(pathFile,"w");
	addressCell Cell;
	int i,j;
	boolean adakolom;
	for (i=1; i<=Worksheet.MAXROW; i++) {
		adakolom = true;
		for (j=1; adakolom && j<=Worksheet.MAXCOLUMN;j++) {
			Cell = getOnlyCell(i,j);
			if (Cell==Nil) {
				adakolom =false;
			} else {
				if (Tipe(Cell) != EMPTY) {
					fprintf(processedFile, "%s %d : ", indeksKolom(j),i);
					if (Tipe(Cell)==FORMULA) {
						fprintf(processedFile, "%s #\n", Formula(Cell));
					} else
					if (Tipe(Cell)==KALIMAT) {
						fprintf(processedFile, "%s #\n", Kalimat(Cell));
					} else
					if (Tipe(Cell)==REAL) {
						fprintf(processedFile, "%.3lf #\n", Real(Cell));
					} else
					if (Tipe(Cell)==INTEGER) {
						fprintf(processedFile, "%d #\n", Integer(Cell));
					} else
					if (Tipe(Cell)==BOOLEAN) {
						fprintf(processedFile, "%s #\n", Boolean(Cell)?"TRUE":"FALSE");
					};
				}
			}
		}
	}
	fprintf(processedFile,"#\n");
	fclose(processedFile);
}
void Display(command Command){
	area Area;
	if (Command.length==1) {
		Area = makeArea("A1:J10");
	} else {
		Area = makeArea(Command.param[1]);
	}
	printSheet(Area);
}

void Write(command Command){
	char ckolom[20],cbaris[20];
	int baris,kolom,i,j;
	addressCell Cell;
	i=0,j=0;
	while ('A'<= Command.param[1][i] && Command.param[1][i] <='Z') {
		ckolom[j] = Command.param[1][i];
		i++; j++;
	}
	ckolom[j] = '\0';
	j = 0;
	while ('0'<= Command.param[1][i] && Command.param[1][i] <='9') {
		cbaris[j] = Command.param[1][i];
		i++; j++;
	}
	cbaris[j] = '\0';
	kolom = nomorKolom(ckolom);
	sscanf(cbaris, "%d",&baris);
	Cell = getCell(baris,kolom);
	insert(Cell, Command.param[2]);
}

void Evaluate(command Command){
	ekspresi Ekspresi;
	makeEkspresi(&Ekspresi,Command.param[0]+1);
}
