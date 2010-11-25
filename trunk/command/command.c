#include "command.h"

void clean(command * Command){
	int i;
	for (i=0; i<5; i++) {
		sstrcpy( (*Command).param[i] , "");
	}
}

command readCommand() {
	char tmp[MAXSTRINGLENGTH];
	int i = 0;
	command Command;
	Command.length = 1;
	clean(&Command);
	scanf("%s", tmp);
	if (tmp[0] == '=') {
		while (sstrcmp(tmp,"#")) {
			sstrcat(Command.param[i], tmp);
			scanf("%s",tmp);
		}
	} else {
		while (sstrcmp(tmp,"#")) {
			Command.length++;
			sstrcpy(Command.param[i++], tmp);
			scanf("%s",tmp);
			
		}
	}
	return Command;
}

int processCommandDocument(command Command){
	if (!sstrcmp(Command.param[0],"list")) List();
	else if (!sstrcmp(Command.param[0],"find")) Find(Command);
	else if (!sstrcmp(Command.param[0],"delete")) Delete(Command);
	else if (!sstrcmp(Command.param[0],"new")) New(Command);
	else if (!sstrcmp(Command.param[0],"open")) Open(Command);
	else if (!sstrcmp(Command.param[0],"exit")) {
		Exit();
		return 0;
	}
	else printf("Command error\n");
	return 1;
}

int processCommandFile(command Command) {
	if (!sstrcmp(Command.param[0],"save")) Save(); else
	if (!sstrcmp(Command.param[0],"display")) Display(Command); else
	if (!sstrcmp(Command.param[0],"close")) return 0; else
	if (!sstrcmp(Command.param[0],"write")) Write(Command); else
	if (!sstrcmp(Command.param[0],"remove")) Remove(Command); else
	if (Command.param[0][1] == '=') Evaluate(Command); else
	printf("Invalid Command!\n");
	return 1;
}
