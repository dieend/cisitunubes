#include "ekspresi.h"

int countStack;
char * getInBracket(char raw[]) {
	/* mengambil semua dalam kurung */
	int i,bracket;
	char* result;
	result = (char*) malloc(MAXSTRINGLENGTH * sizeof(char));
	bracket = 0;
	i = 0;
	do {
		result[i] = raw[i];
		if (raw[i] == '(') bracket++;
		else if(raw[i] ==')') bracket--;
		i++;
	} while (bracket != 0);
	result[i] = '\0';
	return result;
}

ekspresi DoEkspresi(ekspresi Ekspresi) {
	int i,baris,kolom;
	char tipeFormula[MAXSTRINGLENGTH];
	value Value;
	ekspresi argument;
	area Area;
	addressCell Cell;
	argument.error = false;
	for (i=0; i<Ekspresi.length; i++) {
		sstrcpy(tipeFormula,"");
		sscanf(Ekspresi.token[i],"%[^(]",tipeFormula);
//		printf("%s\n",Ekspresi.token[i]);
		if (!sstrcmp(tipeFormula,"SUM")) {
			Area = makeArea(Ekspresi.token[i]+sstrlen(tipeFormula)+1);
			Value = doSUM(Area);
			if (Value.tipeData != FAIL)	sstrcpy(Ekspresi.token[i],Value.KALIMAT); else sstrcpy(Ekspresi.token[i],VERROR);
		} else
		if (!sstrcmp(tipeFormula,"COUNT")) {
			Area = makeArea(Ekspresi.token[i]+sstrlen(tipeFormula)+1);
			Value = doCOUNT(Area);
			if (Value.tipeData != FAIL)	sstrcpy(Ekspresi.token[i],Value.KALIMAT); else sstrcpy(Ekspresi.token[i],VERROR);
		} else
		if (!sstrcmp(tipeFormula,"AVERAGE")) {
			Area = makeArea(Ekspresi.token[i]+sstrlen(tipeFormula)+1);
			Value = doAVERAGE(Area);
			if (Value.tipeData != FAIL)	sstrcpy(Ekspresi.token[i],Value.KALIMAT); else sstrcpy(Ekspresi.token[i],VERROR);
		} else
		if (!sstrcmp(tipeFormula,"STDEV")) {
			Area = makeArea(Ekspresi.token[i]+sstrlen(tipeFormula)+1);
			Value = doSTDEV(Area);
			if (Value.tipeData != FAIL)	sstrcpy(Ekspresi.token[i],Value.KALIMAT); else sstrcpy(Ekspresi.token[i],VERROR);
		} else
		if (!sstrcmp(tipeFormula,"MAX")) {
			Area = makeArea(Ekspresi.token[i]+sstrlen(tipeFormula)+1);
			Value = doMAX(Area);
			if (Value.tipeData != FAIL)	sstrcpy(Ekspresi.token[i],Value.KALIMAT); else sstrcpy(Ekspresi.token[i],VERROR);
		} else
		if (!sstrcmp(tipeFormula,"MIN")) {
			Area = makeArea(Ekspresi.token[i]+sstrlen(tipeFormula)+1);
			Value = doMIN(Area);
			if (Value.tipeData != FAIL)	sstrcpy(Ekspresi.token[i],Value.KALIMAT); else sstrcpy(Ekspresi.token[i],VERROR);
		} else 
		if (!sstrcmp(tipeFormula,"DIV")) {
			argument = makeEkspresi(Ekspresi.token[i]+sstrlen(tipeFormula)+1);
			sstrcpy(Ekspresi.token[i],doDIV(argument));
		} else 
		if (!sstrcmp(tipeFormula,"SQR")) {
			argument = makeEkspresi(Ekspresi.token[i]+sstrlen(tipeFormula)+1);
			sstrcpy(Ekspresi.token[i],doSQR(argument));
		} else 
		if (!sstrcmp(tipeFormula,"SQRT")) {
			argument = makeEkspresi(Ekspresi.token[i]+sstrlen(tipeFormula)+1);
			sstrcpy(Ekspresi.token[i],doSQRT(argument));
		} else 
		if (!sstrcmp(tipeFormula,"MOD")){
			argument = makeEkspresi(Ekspresi.token[i]+sstrlen(tipeFormula)+1);
			sstrcpy(Ekspresi.token[i],doMOD(argument));
		} else 
		if (!sstrcmp(tipeFormula,"IF")) {
			argument = makeIF(Ekspresi.token[i]+sstrlen(tipeFormula)+1);
			sstrcpy(Ekspresi.token[i],doIF(argument));
		} else
		if (!sstrcmp(tipeFormula,"CONCAT")) {
			argument = makeEkspresi(Ekspresi.token[i]+sstrlen(tipeFormula)+1);
			sstrcpy(Ekspresi.token[i],doCONCAT(argument));
		} else 
		if (!sstrcmp(tipeFormula,"AND")) {
			argument = makeEkspresi(Ekspresi.token[i]+sstrlen(tipeFormula)+1);
			sstrcpy(Ekspresi.token[i],doAND(argument));
		} else 
		if (!sstrcmp(tipeFormula,"OR")) {
			argument = makeEkspresi(Ekspresi.token[i]+sstrlen(tipeFormula)+1);
			sstrcpy(Ekspresi.token[i],doOR(argument));
		} else 
		if (!sstrcmp(tipeFormula,"NOT")) {
			argument = makeEkspresi(Ekspresi.token[i]+sstrlen(tipeFormula)+1);
			sstrcpy(Ekspresi.token[i],doNOT(argument));
		} else 
		if (isIndeks(Ekspresi.token[i])){
			makeIndeks(Ekspresi.token[i], &baris, &kolom);
			Cell = getCell(baris,kolom);
			if (Tipe(Cell) == INTEGER) {
				sprintf(Ekspresi.token[i],"%d",Integer(Cell));
			} else if (Tipe(Cell) == REAL) {
				sprintf(Ekspresi.token[i],"%lf",Real(Cell));
			} else if (Tipe(Cell) == FORMULA) {
				argument = makeEkspresi(Formula(Cell)+1);
				if (argument.error)
					sprintf(Ekspresi.token[i],ERROR);
				else
					sprintf(Ekspresi.token[i],"%s",argument.token[0]);
			} else if (Tipe(Cell) == KALIMAT) {
				sprintf(Ekspresi.token[i],"%s",Kalimat(Cell));
			}
		} else if (Ekspresi.token[i][0] == '(') {
			argument = makeEkspresi(Ekspresi.token[i]+sstrlen(tipeFormula)+1);
			sstrcpy(Ekspresi.token[i],argument.token[0]);
		} else {
		} 
	}
//	tulisEkspresi(Ekspresi);
	sstrcpy(Ekspresi.token[0],doArithmatic(Ekspresi));
	Ekspresi.length = 1;
	return Ekspresi;
}

ekspresi makeEkspresi(char rawEkspresi[]){
	/* memecah ekspresi menjadi subekspresi */
	ekspresi Ekspresi;
	char tmp[MAXSTRINGLENGTH];
	int len,i,lentoken,j=0;
	i=0;
	len = sstrlen(rawEkspresi);
	Ekspresi.length = 0;
	Ekspresi.error = false;
	while (i<len) {
		j++;
		sstrcpy(lastToken(Ekspresi),"");
		sscanf(rawEkspresi+i,"%[^=(!<>^+-*/,):]",lastToken(Ekspresi));
//		printf("%d %c\n",i,rawEkspresi[i]);
		lentoken = sstrlen(lastToken(Ekspresi));
		/* jika karakter '(' Jika subekspresi merupakan sebuah formula, digabungin seluruh tokennya sampai ')' */
		if (rawEkspresi[i+lentoken] == '+' || rawEkspresi[i+lentoken] == '-' || rawEkspresi[i+lentoken] == '=' ||
			rawEkspresi[i+lentoken] == '*' || rawEkspresi[i+lentoken] == '/' || rawEkspresi[i+lentoken] == ':' ||
			rawEkspresi[i+lentoken] == '<' || rawEkspresi[i+lentoken] == '>' || rawEkspresi[i+lentoken] == '!') {
			if (lentoken>0) {
//				printf("%s\n",lastToken(Ekspresi));
				i+=lentoken;
				Ekspresi.length++;
			}
			sscanf(rawEkspresi+i,"%[=+-*/<!>^:]",lastToken(Ekspresi));
			if (!sstrcmp(lastToken(Ekspresi),"+-")) {
				sstrcpy(lastToken(Ekspresi),"+");
				i+=2;
				Ekspresi.length++;
				sstrcpy(lastToken(Ekspresi),"-");
				sscanf(rawEkspresi+i,"%[^=(!<>^+-*/,):]",tmp);
				sstrcat(lastToken(Ekspresi),tmp);
				Ekspresi.length++;
				i+=sstrlen(lastToken(Ekspresi));
			} else if (!sstrcmp(lastToken(Ekspresi),"--")) {
				sstrcpy(lastToken(Ekspresi),"-");
				i+=2;
				Ekspresi.length++;
				sstrcpy(lastToken(Ekspresi),"-");
				sscanf(rawEkspresi+i,"%[^=(!<>^+-*/,):]",tmp);
				sstrcat(lastToken(Ekspresi),tmp);
				Ekspresi.length++;
				i+=sstrlen(lastToken(Ekspresi));
			} else {
				i+=sstrlen(lastToken(Ekspresi));
				Ekspresi.length++;
			}
		} else
		if (rawEkspresi[i+lentoken] == ',' || rawEkspresi[i+lentoken] == ')') {
			if (lentoken>0) {
//				printf("%s\n",lastToken(Ekspresi));
				i+=lentoken;
				Ekspresi.length++;
			}
			i++;
		} else
		if (rawEkspresi[i+lentoken]=='(') {
			sstrcat(lastToken(Ekspresi),getInBracket(rawEkspresi+i+lentoken));
			i+=sstrlen(lastToken(Ekspresi));
			Ekspresi.length++;
		} else {
			i+=sstrlen(lastToken(Ekspresi));
			Ekspresi.length++;
		}
//		printf("%d %s\n",i,Ekspresi.token[Ekspresi.length-1]);
//		if (j==10) break;
	}
//	tulisEkspresi(Ekspresi);
//	DEBUG;
	countStack++;
	if (countStack>MAXSTACK) {
		Ekspresi.error = true;
		return Ekspresi;
	}
	return (DoEkspresi(Ekspresi));
}
ekspresi makeIF(char rawEkspresi[]){
	ekspresi Ekspresi,argument;
	char arg1[MAXSTRINGLENGTH];
	int i = 0;
	Ekspresi.length = 3;
	sscanf(rawEkspresi,"%[^,]",arg1);
	i+=sstrlen(arg1)+1;
	argument = makeEkspresi(arg1);
	sstrcpy(Ekspresi.token[0],argument.token[0]);
	sscanf(rawEkspresi+i,"%[^,]",arg1);
	i+=sstrlen(arg1)+1;
	argument = makeEkspresi(arg1);
	sstrcpy(Ekspresi.token[1],argument.token[0]);
	sscanf(rawEkspresi+i,"%[^)]",arg1);
	argument = makeEkspresi(arg1);
	sstrcpy(Ekspresi.token[2],argument.token[0]);
	return (DoEkspresi(Ekspresi));
}
void tulisEkspresi(ekspresi Ekspresi) {
	int i;
//	puts("OK");
	for (i=0; i<Ekspresi.length; i++) {
		printf("%s\n",Ekspresi.token[i]);
	}
}


