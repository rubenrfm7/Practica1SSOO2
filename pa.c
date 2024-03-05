#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>

int main() {
    prinf("Proceso A creando directorios\n");
    FILE *file = fopen("estudiantes.txt", "r");
    if (file == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    char line[100];
    while (fgets(line, sizeof(line), file)) {
        char dni[20];
        sscanf(line, "%s", dni);
        if (mkdir(dni, 0777) == -1) {
            if (errno != EEXIST) {  
            }
        }
    }
    fclose(file);
    printf("Proceso A terminado\n");
    exit(0);
}