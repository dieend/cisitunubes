#ifndef worksheet_H
#define worksheet_H

#include "../command/command.h"
#define MAXWORKSIZE 10
#define Nil NULL

enum tipe {
	EMPTY, REAL, KALIMAT, FORMULA, INTEGER, BOOLEAN, FAIL
};
typedef struct {
	union {
		double REAL;
		char KALIMAT[100];
		char FORMULA[100];
		int INTEGER;
		boolean BOOLEAN;
	};
	enum tipe tipeData;
} value;


typedef struct tcell * addressCell;
typedef struct tcell{
	value nilai;
	addressCell NextRow;
	addressCell NextCol;
} cell;

/** Selektor Cell **/
/* c bertipe address Cell */
#define Tipe(c) (c)->nilai.tipeData
#define Real(c) (c)->nilai.REAL
#define Formula(c) (c)->nilai.FORMULA
#define Integer(c) (c)->nilai.INTEGER
#define Kalimat(c) (c)->nilai.KALIMAT
#define Boolean(c) (c)->nilai.BOOLEAN
#define NextR(c) (c)->NextRow
#define NextC(c) (c)->NextCol

typedef struct tHeader* addressHeader;
typedef struct tHeader{
	int Nomor;
	addressCell  firstElmt;
	addressHeader next;
} header;

typedef struct {
	addressHeader hBaris;
	addressHeader hKolom;
	int MAXROW,MAXCOLUMN;
} worksheet;

typedef struct {
	int rUL,cUL, rLR, cLR;
} area;

addressHeader alokasiHeader(int x);
addressCell alokasiCell() ;
extern worksheet Worksheet;
void alokasiWorksheet();
addressCell getCell(int r, int c);
addressCell getOnlyCell(int r, int c);
void inverse(char inver_a[],int j);
char * indeksKolom(int n);
int nomorKolom(char kolom[]);
boolean isArea(char Cek[]);
boolean isIndeks(char Cek[]);
area makeArea(char Area[]);
void makeEmpty(area Area);
void makeIndeks(char tmp[], int * baris, int * kolom);
void printSheet(area Area);
void insert(addressCell Cell, char isi[]);
value doSUM(area Area);
value doCOUNT(area Area) ;
value doAVERAGE(area Area);
value doSTDEV(area Area) ;
value doMAX(area Area) ;
value doMIN(area Area);
#endif
