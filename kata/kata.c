#include "kata.h"

int sstrlen(char kata[]){
	int i=0;
	while (kata[i] != '\0') {
		i++;
	}
	return i;
}

void sstrcat(char kata1[], char kata2[]){
	int i,j;
	i=sstrlen(kata1);
	j=0;
	while (kata2[j] != '\0') {
		kata1[i] = kata2[j];
		i++; j++;
	}
	kata1[i] = '\0';
}

void sstrcpy(char kata1[], char kata2[]){
	int i=0;
	while (kata2[i] != '\0') {
		kata1[i] = kata2[i];
		i++;
	}
	kata1[i] = '\0';
}

int sstrcmp(char kata1[], char kata2[]) {
	int dif,i;
	i = 0; dif = 0;
	while (kata1[i] != '\0' && kata2[i] !='\0') {
		if (kata1[i] != kata2[i]) dif++;
		i++;
	}
	if (kata1[i] != '\0') dif += (sstrlen(kata1)-sstrlen(kata2));
	if (kata2[i] != '\0') dif += (sstrlen(kata2)-sstrlen(kata1));
	return dif;
}

boolean isSubString(char kata1[], char kata2[]) {
	int len1,len2;
	int i,j,k;
	len1 = sstrlen(kata1);
	len2 = sstrlen(kata2);
	for (i=0; i<len1; i++) {
		j=0;
		k=i;
		while (j<len2 && kata1[k]==kata2[j]) {
			j++; k++;
		}
		if (j==len2) return true;
	}
	return false;
}
