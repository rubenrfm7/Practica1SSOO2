#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>

int main() {
    //Mostramos por pantalla que el proceso A ha inicidado
    printf("Proceso A creando directorios\n");
    //Abrimpos el archivo estudiantes.txt en modo lectura
    FILE *file = fopen("estudiantes.txt", "r");
    //Capturamos el error en caso de que no se pueda abrir
    if (file == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    
    // Declarar un array para almacenar cada línea del archivo
    char line[100];
    // Leer el archivo línea por línea
    while (fgets(line, sizeof(line), file)) {
        char dni[20];
        // Analizar la línea para extraer el DNI del estudiante 
        sscanf(line, "%s", dni);
        //Creamos el directorio del estudiante en funcion de su DNI
        if (mkdir(dni, 0777) == -1) {
            if (errno != EEXIST) {  
                // Manejar el error si el directorio ya existe
            }
        }
    }
    //Cerramos el archivo estudiantes.txt 
    fclose(file);
    // Imprimir un mensaje de finalización
    printf("Proceso A terminado\n");
    exit(0);
}