#include "ekspresi.h"
#include "../worksheet/worksheet.h"

int main() {
	alokasiWorksheet();
	insert(getCell(1,1),"10");
	insert(getCell(1,2),"15");
	printSheet(makeArea("A1:B4"));
	char coba[MAXSTRINGLENGTH];
	while (scanf("%s",coba) != EOF) {
		printf("%s menjadi :\n",coba);
		tulisEkspresi(makeEkspresi(coba));
		puts("OK");
	}
	return 0;
}
