#include "worksheet.h"

worksheet Worksheet;

addressHeader alokasiHeader(int x) {
	addressHeader Header;
	Header = (addressHeader) malloc (1*sizeof(header));
	if (Header == Nil) {
		printf("ALOKASI GAGAL!!\n");
		return Nil;
	}
	Header->Nomor = x;
	Header->firstElmt = alokasiCell();
	Header->next = Nil;
	return Header;
}

addressCell alokasiCell() {
	addressCell Cell;
	Cell = (addressCell) malloc(1*sizeof(cell));
	if (Cell == Nil) {
		printf("ALOKASI CELL GAGAL!!!\n");
		return Nil;
	};
	Tipe(Cell) = EMPTY;
	NextR(Cell) = Nil;
	NextC(Cell) = Nil;
	return Cell;
}

void alokasiWorksheet(){
	int i,j;
	addressHeader Header;
	addressCell Cell;
	Worksheet.hBaris = alokasiHeader(1);
	Header = Worksheet.hBaris;
	for (i=2; i<MAXWORKSIZE+10; i++) {
		Header->firstElmt = alokasiCell();
		Cell = Header->firstElmt;
		for (j=1; j<MAXWORKSIZE+1;j++) {
			NextC(Cell) = alokasiCell();
			Cell = NextC(Cell);
//			printf("%d\n",j);
		}
		Header->next = alokasiHeader(i);
		Header = Header->next;
	}
	
	Worksheet.hKolom = alokasiHeader(1);
	Header = Worksheet.hKolom;
	for (i=0; i<MAXWORKSIZE+1; i++) {
//		printf("%d\n",i);
		Header->next = alokasiHeader(i+2);
		for (j=0; j<MAXWORKSIZE; j++) {
			Cell = getCell(i,j);
			NextR(Cell) = getCell(i+1,j);
		}
		Header = Header->next;
	}
	Worksheet.MAXCOLUMN = 10;
	Worksheet.MAXROW = 10;
}

addressCell getCell(int r, int c) {
	int i,j;
	addressCell Cell;
	addressHeader Header = Worksheet.hBaris;
	for (i=0; i<r; i++) {
		if (Header->next != Nil) {
			Header = Header->next;
		} else {
			Worksheet.MAXROW = Worksheet.MAXROW < r?r:Worksheet.MAXROW;
			Header->next = alokasiHeader(i+1);
			Header = Header->next;
		}
	}
	Cell = Header->firstElmt;
	for (j=0; j<c; j++) {
		if (NextC(Cell) != Nil) {
			Cell = NextC(Cell);
		} else  {
			Worksheet.MAXCOLUMN = Worksheet.MAXCOLUMN<r? r:Worksheet.MAXCOLUMN;
			NextC(Cell) = alokasiCell();
			Cell = NextC(Cell);
		}
	}
	return Cell;
}


addressCell getOnlyCell(int r, int c) {
	int i,j;
	addressCell Cell;
	addressHeader Header = Worksheet.hBaris;
	for (i=0; i<r; i++) {
		if (Header->next != Nil) {
			Header = Header->next;
		} else {
			return Nil;
		}
	}
	Cell = Header->firstElmt;
	for (j=0; j<c; j++) {
		if (NextC(Cell) != Nil) {
			Cell = NextC(Cell);
		} else  {
			return Nil;
		}
	}
	return Cell;
}


void inverse(char inver_a[],int j)
{
   int i,temp,x;
   x = j;
   j--;
   for(i=0;i<(x/2);i++)
   {
      temp=inver_a[i];
      inver_a[i]=inver_a[j];
      inver_a[j]=temp;
      j--;
   }
}

char * indeksKolom(int n) {
	char* indeks;
	n--;
	indeks = (char*) malloc(20*sizeof(char));
	int chr,len = 0;
	char tmp[2];
	sstrcpy(indeks,"");
	sstrcpy(tmp,"A");
	chr = n%26;
	tmp[0]=(char)(chr+('A'));
	sstrcat(indeks,tmp);
	len++;
	n/=26;
	while (n>0) {
		n--;
		chr = n%26;
		tmp[0]=(char)(chr+('A'));
		sstrcat(indeks,tmp);
		len++;
		n/=26;
	}
	inverse(indeks, len);
	return indeks;
}

int nomorKolom(char kolom[]) {
	int n,len,mult;
	mult = 1;
	n=0;
	len = sstrlen(kolom)-1;
//	printf("%s\n",kolom);
	while (len>=0) {
		n += (int) (kolom[len]-'A'+1) * mult;
//		printf("%d\n",n);
//		printf("%d",len);
		mult*=26;
		len--;
	}
	return n;
}

boolean isArea(char Cek[]) {
	int i,len;
	len = sstrlen(Cek);
	for (i=0; i<len; i++) {
		if (Cek[i] == ':') return true;
	}
	return false;
}
boolean isIndeks(char Cek[]){
	int i = 0,len;
	len = sstrlen(Cek);
	for (i=0; i<len && ('A'<=Cek[i] && Cek[i] <= 'Z'); i++);
	for (i=i; i<len && ('0'<=Cek[i] && Cek[i] <='9'); i++);
	return (i==len);
}

void makeIndeks(char tmp[], int * baris, int * kolom) {
	int i=0,j=0;
	char ckolom[MAXSTRINGLENGTH], cbaris[MAXSTRINGLENGTH];
	while ('A'<= tmp[i] && tmp[i] <='Z') {
		ckolom[j] = tmp[i];
		i++; j++;
	}
	ckolom[j] = '\0';
	j = 0;
	while ('0'<= tmp[i] && tmp[i] <='9') {
		cbaris[j] = tmp[i];
		i++; j++;
	}
	cbaris[j] = '\0';
	*kolom = nomorKolom(ckolom);
	sscanf(cbaris, "%d",baris);
}
area makeArea(char tmp[]) {
	area Area;
	char cArea[50];
	if (isArea(tmp)) {
		sstrcpy(cArea,tmp);
	} else {
		sstrcpy(cArea,tmp);
		sstrcat(cArea,":");
		sstrcat(cArea,tmp);
	}
	int i,j;
	char cindeks[50];
	i=0; j=0;
	while ('A' <= cArea[i] && cArea[i] <= 'Z') {
		cindeks[j] = cArea[i];
		i++; j++;
	}
	cindeks[j] = '\0';
	Area.cUL = nomorKolom(cindeks);
	j=0;
	while ('0' <= cArea[i] && cArea[i] <= '9') {
		cindeks[j] = cArea[i];
		i++; j++;
	}
	sscanf(cindeks, "%d",&Area.rUL);
	i++;
	j=0;
	while ('A' <= cArea[i] && cArea[i] <= 'Z') {
		cindeks[j] = cArea[i];
		i++; j++;
	}
	cindeks[j] = '\0';
	Area.cLR = nomorKolom(cindeks);
	j=0;
	while ('0' <= cArea[i] && cArea[i] <= '9') {
		cindeks[j] = cArea[i];
		i++; j++;
	}
	sscanf(cindeks, "%d",&Area.rLR);
	return Area;
}

void printSheet(area Area) {

	int i,j;
	addressCell Cell;
	ekspresi Ekspresi;
//	char tmp[MAXSTRINGLENGTH];
	printf("%-10s","");
	for (i=Area.cUL; i<=Area.cLR; i++) {
		printf("%-10s", indeksKolom(i));
	}
	printf("\n");
	for (i=Area.rUL; i<=Area.rLR; i++) {
		printf("%-10d", i);
		for (j=Area.cUL; j<=Area.cLR;j++) {
			countStack = 0;
			Cell = getCell(i,j);
			if (Tipe(Cell) == KALIMAT) {
				printf("%-10s", Kalimat(Cell)+1);
			} else
			if (Tipe(Cell) == INTEGER) {
				printf("%-10d", Integer(Cell));
			} else
			if (Tipe(Cell) == REAL) {
				printf("%-10.2lf", Real(Cell));
			} else
			if (Tipe(Cell) == FORMULA) {
//				sstrcpy(tmp,Formula(Cell));
				Ekspresi = makeEkspresi(Formula(Cell)+1);
				if (Ekspresi.error) printf(ERROR); else
				if (Ekspresi.token[0][0] =='\'')
					printf("%-10s",Ekspresi.token[0]+1);
				else
					printf("%-10s",Ekspresi.token[0]);
			} else          
			if (Tipe(Cell) == BOOLEAN) {
				printf("%-10s", Boolean(Cell)?"TRUE":"FALSE");
			} else 
			if (Tipe(Cell) == EMPTY) {
				printf("%-10s","");          
			}
			
		}
		printf("\n");
	}
}

void makeEmpty(area Area){
	int i,j;
	addressCell Cell;
	for (i=Area.rUL; i<=Area.rLR; i++) {
		for (j=Area.cUL;j<=Area.cLR; j++) {
			Cell = getCell(i,j);
			Tipe(Cell) = EMPTY;
		}
	}
}


void insert(addressCell Cell, char isi[]) {
	if (isi[0] == '=') {
		Tipe(Cell) = FORMULA;
		sstrcpy(Formula(Cell),isi);
	} else if (isi[0] == '\'') {
		Tipe(Cell) = KALIMAT;
		sstrcpy(Kalimat(Cell),isi);
	} else if (adaKoma(isi)) {
		Tipe(Cell) = REAL;
		sscanf(isi, "%lf",&Real(Cell));
	} else if (angkaSemua(isi)) {
		Tipe(Cell) = INTEGER;
		sscanf(isi, "%d", &Integer(Cell));
	} else if ((!sstrcmp(isi,"TRUE") || !sstrcmp(isi,"FALSE"))) {
		Tipe(Cell) = BOOLEAN;
		Boolean(Cell) = (sstrcmp(isi,"TRUE")?false:true);
	} else {
		printf("Data tidak valid\n");
	}
}

value doSUM(area Area) { 
	int iSum = 0,i,j;
	double dSum = 0, tmp = 0;
	value Value;
	addressCell Cell;
	ekspresi Ekspresi;
	boolean isDouble = false;
	Value.tipeData = EMPTY;
	
	for (i=Area.rUL; i<=Area.rLR && Value.tipeData != FAIL; i++) {
		for (j=Area.cUL; j<=Area.cLR && Value.tipeData != FAIL; j++) {
			Cell = getCell(i,j);
			if (Tipe(Cell) == INTEGER) {
				iSum += Integer(Cell);
			} else if (Tipe(Cell) == REAL) {
				dSum += Real(Cell);
				isDouble = true;
			} else if (Tipe(Cell) == FORMULA) {
				Ekspresi = makeEkspresi(Formula(Cell)+1);
				sscanf(Ekspresi.token[0],"%lf",&tmp);
				dSum += tmp;
				isDouble = true;
			} else if (Tipe(Cell) != EMPTY) {
				Value.tipeData = FAIL;
			}
		}
	}
	if (Value.tipeData!=FAIL) Value.tipeData = KALIMAT;
	if (isDouble)
		sprintf(Value.KALIMAT,"%.2lf",(double) iSum + dSum);
	else
		sprintf(Value.KALIMAT,"%d",iSum);
	return Value;
}

value doCOUNT(area Area) { 
	value Value;
	addressCell Cell;
	int Count = 0,i,j;
	Value.tipeData = EMPTY;
	for (i=Area.rUL; i<=Area.rLR && Value.tipeData != FAIL; i++) {
		for (j=Area.cUL; j<=Area.cLR && Value.tipeData != FAIL; j++) {
			Cell = getCell(i,j);
			if (Tipe(Cell) != EMPTY) {
				Count+=1;
			}
		}
	}
	if (Value.tipeData!=FAIL) Value.tipeData = KALIMAT;
	sprintf(Value.KALIMAT,"%d",Count);
	return Value;
}

value doAVERAGE(area Area) { 
	value Value;
	double sum;
	int Count;
	Value = doSUM(Area);
	if (Value.tipeData!=FAIL) {
		sscanf(Value.KALIMAT,"%lf",&sum);
		Value = doCOUNT(Area);
		sscanf(Value.KALIMAT,"%d",&Count);
		sprintf(Value.KALIMAT,"%.3lf",sum/(double)Count) ;
	}
	return Value;
}

value doSTDEV(area Area) { 
	value Value;
	return Value;
}

value doMAX(area Area) { 
	value Value;
	return Value;
}
value doMIN(area Area) { 
	value Value;
	return Value;
}
