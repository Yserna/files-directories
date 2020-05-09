#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char * argv[]) {
	FILE * file;
    char str[1000];
	int c, n = abs(atoi(argv[1]));
	unsigned long long lines;
	int linea = 0;	

	if (argc != 3) {
		printf("Ingrese los parámetros correctamente\n");
        return 0;
	}

	if ((file = fopen(argv[2], "r")) == NULL) {
		perror("fallo abriendo el archivo");
        return 0;
	}

	if ((fseek(file, 0, SEEK_END) == -1) || (fseek(file, -1, SEEK_CUR) == -1)) {
		printf("Seek falló.");
        return 0;
	}

	lines = ftell(file);

	while(lines) {
		if ((c = fgetc(file)) == '\n') {
			linea++;
		}
		if (c == EOF) {
			break;
		}
		if (n <= linea) {
			break;
		}
		if (ungetc(c, file) == EOF){
			printf("falló ungetc.");
			exit(-1);
		}
		fseek(file, -1, SEEK_CUR);
	}

	while (fgets(str, 1000, file) != NULL) {
		printf("%s", str);
	}
	printf("\n");
	
	return 0;
}