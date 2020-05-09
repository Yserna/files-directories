#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

int main(int argc, char *argv[]) {

    struct stat buffer;
    if(stat(argv[1], &buffer) < 0){
        printf("No se encontró el archivo.\n");
        return 1;
    }
 
    printf("Datos del archivo: %s\n", argv[1]);
    printf("---------------------------\n");
    printf("Permisos del Archivo: %d\n", buffer.st_mode);
    printf("Tamaño archivo: %ld bytes\n", buffer.st_size);
    printf("Número de Links: %ld\n", buffer.st_nlink);
    printf("Número de Bloques: %ld\n", buffer.st_blocks);
    printf("Tamaño de Bloques: %ld\n", buffer.st_blksize);
    printf("Archivo node-i: %ld\n", buffer.st_ino);
    printf("\n\n");

    printf ("Último acceso:%s", ctime (& buffer.st_atime)); 
    printf ("Último cambio de estado:%s", ctime (& buffer.st_ctime)); 
    printf ("Última modificación del archivo:%s", ctime (& buffer.st_mtime));

    printf("\nEl archivo %s un  link simbolico\n", (S_ISLNK(buffer.st_mode)) ? "es" : "no es");

    return 0;
}