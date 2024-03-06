#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>

#define MAX_PATH_LENGTH 260
#define MAX_COMMAND_LENGTH 520

int main() {
    // Mensaje indicando el comienzo del proceso D
    printf("Proceso PD en ejecución para limpiar contenido creado.\n");
    
    // Abrir el directorio actual
    DIR *dir = opendir(".");
    struct dirent *entry;
    // Iterar sobre todos los archivos y directorios en el directorio actual
    while ((entry = readdir(dir)) != NULL) {
        // Saltar los archivos ocultos y el directorio "examenes"
        if (entry->d_name[0] != '.' && strcmp(entry->d_name, "examenes") != 0) {
            // Construir la ruta completa del archivo o directorio
            char path[MAX_PATH_LENGTH];
            snprintf(path, sizeof(path), "./%s", entry->d_name);
            
            // Obtener información sobre el archivo o directorio
            struct stat statbuf;
            if (lstat(path, &statbuf) == 0 && S_ISDIR(statbuf.st_mode)) {
                // Si es un directorio,  ejecutamos el comando para eliminarlo recursivamente
                char command[MAX_COMMAND_LENGTH];
                snprintf(command, sizeof(command), "rm -rf %s", path);
                system(command);
            }
        }
    }
    // Cerrar el directorio
    closedir(dir);

    // Abrir el archivo de log en modo anexion para escribir a continuación
    FILE *log_file = fopen("log.txt", "a");
    time_t current_time = time(NULL);
    struct tm *local_time = localtime(&current_time);
    if (log_file != NULL) {
        fprintf(log_file, "Fecha y hora: %s", asctime(local_time));
        fprintf(log_file, "Interrupción voluntaria ordenada por el propio usuario.\n");
        fclose(log_file);
    } else {
        // Manejar el error si no se puede abrir el archivo de registro
        perror("fopen");
    }
    
    // Mensaje indicando el final del proceso D
    printf("Proceso D terminado\n");
    
    exit(0);
}