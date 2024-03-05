#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    printf("El proceso C calculando notas necesarias para superar la prueba\n");
    FILE *file = fopen("estudiantes.txt", "r");
            if (file == NULL) {
                perror("fopen");
                exit(EXIT_FAILURE);
            }
            int nestudiantes = 0;
            int sumadenotas = 0;
            char line[100];
            while (fgets(line, sizeof(line), file)) {
                char dni[20], exam_model[2];
                int nota_primera_prueba;
                sscanf(line, "%s %s %d", dni, exam_model, &nota_primera_prueba);
                char student_dir[100];
                snprintf(student_dir, sizeof(student_dir), "%s", dni);
                float nota_necesaria = (5.0 + nota_primera_prueba) / 2;
                char mensaje[100];
                snprintf(mensaje, sizeof(mensaje), "La nota que debes obtener en este nuevo examen para superar la prueba es %.2f.", nota_necesaria);
                char estudiante_info_path[200];
                snprintf(estudiante_info_path, sizeof(estudiante_info_path), "%s/info.txt", student_dir);
                FILE *estudiante_info_file = fopen(estudiante_info_path, "w");
                if (estudiante_info_file != NULL) {
                    fprintf(estudiante_info_file, "%s\n", mensaje);
                    fclose(estudiante_info_file);
                } else {
                    perror("fopen");
                    exit(EXIT_FAILURE);
                }
                nestudiantes++;
                sumadenotas += nota_primera_prueba;
            }
            float nota_media = (float)sumadenotas / nestudiantes;
            char buffer[20];
            snprintf(buffer, sizeof(buffer), "%.2f", nota_media);
            write(atoi(argv[0]), buffer, strlen(buffer) + 1);
            fclose(file);
            printf("Proceso C terminado\n");
            exit(0);
}