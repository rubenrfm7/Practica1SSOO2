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

int main(){
    printf("Proceso PD en ejecución para limpiar contenido creado.\n");
    DIR *dir = opendir(".");
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] != '.' && strcmp(entry->d_name, "examenes") != 0){
            char path[MAX_PATH_LENGTH];
            snprintf(path, sizeof(path), "./%s", entry->d_name);
            struct stat statbuf;
            if (lstat(path, &statbuf) == 0 && S_ISDIR(statbuf.st_mode)) {
                char command[MAX_COMMAND_LENGTH];
                snprintf(command, sizeof(command), "rm -rf %s", path);
                system(command);
        }
    }
}
closedir(dir);

    FILE *log_file = fopen("log.txt", "a");
    time_t current_time = time(NULL);
    struct tm *local_time = localtime(&current_time);
    if (log_file != NULL) {
        fprintf(log_file, "Fecha y hora: %s", asctime(local_time));
        fprintf(log_file, "Interrupción voluntaria ordenada por el propio usuario.\n");
        fclose(log_file);
    } else {
        perror("fopen");
    }
    printf("Proceso D terminado\n");
    exit(0);
}