#include <dirent.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>
#include <sys/types.h>
#include <string.h> 

int main(int argc, char *argv[]) {

     if (argc == 1){
        struct dirent *file;
        DIR *dir = opendir(".");
        if (dir) {
            while ((file = readdir(dir)) != NULL) { 
                printf("%s\n", file->d_name);
            }
            closedir(dir);
        } else {
            printf("No se encontró el archivo.\n");
        }
        return 0;
    }

    if(argc == 2 && strcmp(argv[1],"-l") == 0){
        struct dirent *file;
        struct stat buffer;
        DIR *dir = opendir(".");
        if (dir == NULL){
            printf("Error al abrir el directorio\n");
            return 1;
        } else {
            while ((file = readdir(dir)) != NULL){
                if(stat(file->d_name, &buffer) < 0){
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
            }
        }
        closedir(dir);  
        return(0);
    }

    if(argc == 3 && (strcmp(argv[1],"-l") == 0)){
        char cwd[256];
        if (getcwd(cwd, sizeof(cwd)) != NULL){

            const size_t l1 = strlen(cwd);
            const size_t l2 = strlen(argv[2]);
            char *result = malloc(l1 + l2 + 1);

            memcpy(result, cwd, l1);
            memcpy(result + l1, argv[2], l2 + 1);

            printf("Directorio: %s\n", result);

            struct dirent *file;
            struct stat buffer;
            DIR *dir = opendir(".");
            if (dir == NULL){
                printf("Error al abrir el directorio\n");
                return 1;
            } else {
                while ((file = readdir(dir)) != NULL) { 

                    if(stat(file->d_name, &buffer) < 0)    
                        return 1;
                    printf("---------------------------\n");
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
                } 
            }
            closedir(dir);
            return(0);
        }
    }
    return(0);
}