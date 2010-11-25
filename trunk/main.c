#include "command/command.h"

int main(int argc, char *argv[]) {
	if (argc<2) {
		fprintf(stderr,"sintaks : %s <nama-file>\n", argv[0]);
		exit(1);
	} else {
		FXINT = fopen(argv[1],"r");
		if (!FXINT) {
			FXINT = fopen(argv[1],"w");
			fprintf(FXINT,"files #\n#\n");
			fclose(FXINT);
			FXINT = fopen(argv[1],"r");
		}
	}
	transferDirectory();
	fclose(FXINT);
	FXINT = fopen(argv[1],"w");
	do {
		printf(">");
	} while (processCommandDocument(readCommand()));
	return 0;
}
