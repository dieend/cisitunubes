#include "directory.h"
directory Dir;
FILE * FXINT;
void transferDirectory() {
	int i = 0;
	FILE * akses;
	char tmp[MAXSTRINGLENGTH];
	system("ls -l data > tmp");
	akses = fopen("tmp","r");
	fscanf(akses,"%*[^\n]\n");
	while (fscanf(akses,"%s", tmp) != EOF) {
		fscanf(akses,"%s %s %s",tmp,tmp,tmp);
		fscanf(akses,"%s",Dir.size[i]);
		fscanf(akses,"%s",Dir.date[i]);
		fscanf(akses,"%s",Dir.hour[i]);
		fscanf(akses,"%s",Dir.name[i++]);
	}
	fclose(akses);
	system("du -shS data > tmp");
	akses = fopen("tmp","r");
	fscanf(akses,"%s",Dir.sum);
	Dir.all = i;
	fclose(akses);	
	system("rm tmp");
}

void Find(command Command){
	if (!sstrcmp(Command.param[1],"name")) searchName(Command.param[2]); else
	if (!sstrcmp(Command.param[1],"date")) searchDate(Command.param[2]); else
	if (!sstrcmp(Command.param[1],"size")) searchSize(Command.param[2]);
}

void Open(command Command){
	char path[MAXSTRINGLENGTH];
	int i,len;
	boolean ada = false;
	len = sstrlen(Command.param[1]);
	sstrcpy(path,"data/");
	for (i=0; !ada && i<Dir.all; i++) {
		if (sstrlen(Dir.name[i]) == len+4 && isSubString(Dir.name[i],Command.param[1])) ada = true;
	}
	if (!ada) printf("File tidak ditemukan\n"); else {
		sstrcat(path,Command.param[1]);
		sstrcat(path,ekstensi);
		doModusFile(path);	
	}
}

void New(command Command) {
	char path[MAXSTRINGLENGTH];
	sstrcpy(path,"./data/");
	sstrcat(path,Command.param[1]);
	sstrcat(path,ekstensi);
	FILE * tmp = fopen(path, "w");
	fprintf(tmp, "#\n");
	fclose(tmp);
	transferDirectory();
	Open(Command);
}


void Delete(command Command){
	int i;
	char act[MAXSTRINGLENGTH];
	char fileDelete[MAXSTRINGLENGTH];
	boolean adaFile = false, deleteAll = false;
	
	sstrcpy(fileDelete,Command.param[1]);
	sstrcat(fileDelete,ekstensi);
	if (sstrlen(Command.param[1]) == 0) {
		deleteAll = true;
	}
	if (deleteAll) {
		printf("Are you sure to delete all files? (y/n) :  ");
		scanf("%s",act);
		if (act[0]=='n') return;
		sstrcpy(act,"rm data/*");
		sstrcat(act," > tmp");
		system(act);
		system("rm tmp");
		transferDirectory();
		sstrcpy(Dir.sum,"0");	
	} else {	
		for (i=0; i<Dir.all; i++) {
			if (!sstrcmp(fileDelete,Dir.name[i])) {
				adaFile = true;
				break;
			}
		}
		
		if (adaFile) {
			sstrcpy(act,"rm data/");
			sstrcat(act,Command.param[1]);
			sstrcat(act,ekstensi);
			sstrcat(act,"> tmp");
			system(act);
			system("rm tmp");
			transferDirectory();
		} else {
			printf("Can't found file!\n");
		}
	}
}

void Exit(){
	int i;
	fprintf(FXINT,"data #\n");
	for (i=0; i<Dir.all; i++) {
		fprintf(FXINT,"%s %s %s %s #\n", Dir.name[i], Dir.date[i], Dir.hour[i], Dir.size[i]);
	}
	fprintf(FXINT,"#\n");
	fclose(FXINT);
}
void searchName(char* Name) {
	int i;
	for (i=0; i<Dir.all; i++) {
		if (isSubString(Dir.name[i], Name)) {
			printf("%s\n",Dir.name[i]);
		}
	}
}

void searchDate(char* Date){
	int i;
	for (i=0; i<Dir.all; i++) {
		if (isSubString(Dir.date[i],Date)) {
			printf("%-10s %s\n",Dir.name[i], Dir.date[i]);
		}
	}
}

void searchSize(char* Size){
	int i;
	for (i=0; i<Dir.all; i++) {
		if (isSubString(Dir.size[i],Size)) {
			printf("%-10s %s\n",Dir.name[i], Dir.size[i]);
		}
	}
}

void List(){
	int i;
	printf("data\n");
	for (i=0; i<Dir.all; i++) {
		printf("%-20s %10s %6s %s bytes\n", Dir.name[i], Dir.date[i], Dir.hour[i], Dir.size[i]);
	}
	printf("Banyaknya file = %d\n", Dir.all);
	printf("Ukuran directory = %s\n", Dir.sum);
}
