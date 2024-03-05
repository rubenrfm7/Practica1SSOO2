#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>

void generate_path(char *exam_path, char *exam_model) {
    if (strcmp(exam_model, "A") == 0) {
        strcpy(exam_path, "examenes/MODELOA.pdf");
    } else if (strcmp(exam_model, "B") == 0) {
        strcpy(exam_path, "examenes/MODELOB.pdf");
    } else if (strcmp(exam_model, "C") == 0) {
        strcpy(exam_path, "examenes/MODELOC.pdf");
    } else {
        printf("Modelo de examen no válido.\n");
        exit(EXIT_FAILURE);
    }
}
int main(){
    printf("Proceso B introduciendo examenes en directorios de estudiantes\n");
    FILE *file = fopen("estudiantes.txt", "r");
        if (file == NULL) {
            perror("fopen");
            exit(EXIT_FAILURE);
        }
        char line[100];
        while (fgets(line, sizeof(line), file)) {
            char dni[20], exam_model[2];
            sscanf(line, "%s %s", dni, exam_model);
            char exam_path[100];
            generate_path(exam_path, exam_model);
            char student_dir[100];
            snprintf(student_dir, sizeof(student_dir), "%s", dni);
            if (access(exam_path, F_OK) != -1) {
                char dest_path[200];
                snprintf(dest_path, sizeof(dest_path), "%s/examen.pdf", student_dir);
                if (link(exam_path, dest_path) == -1) {
                    
                }
            } else {
                fprintf(stderr, "El modelo de examen %s.pdf no existe.\n", exam_model);
                exit(EXIT_FAILURE);
            }
        }
        fclose(file);
        printf("Proceso B terminado\n");
        exit(0);
}