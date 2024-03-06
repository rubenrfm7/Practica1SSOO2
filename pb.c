#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>

// Función para generar la ruta del archivo de examen basada en el modelo de examen proporcionado
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

int main() {

    //Informamos que se ha inicidado el proceso B
    printf("Proceso B introduciendo exámenes en directorios de estudiantes\n");

    // Abrir el archivo de texto "estudiantes.txt" en modo lectura
    FILE *file = fopen("estudiantes.txt", "r");
    if (file == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    // Declarar un array para almacenar cada línea del archivo
    char line[100];

    // Leer el archivo línea por línea
    while (fgets(line, sizeof(line), file)) {
        char dni[20], exam_model[2];

        // Analizar la línea para extraer el DNI del estudiante y el modelo de examen
        sscanf(line, "%s %s", dni, exam_model);

        // Crear la ruta del archivo de examen basada en el modelo proporcionado
        char exam_path[100];
        generate_path(exam_path, exam_model);

        // Crear la ruta del directorio del estudiante
        char student_dir[100];
        snprintf(student_dir, sizeof(student_dir), "%s", dni);

        // Verificar si el archivo de examen existe
        if (access(exam_path, F_OK) != -1) {
            // Crear la ruta de destino del enlace simbólico
            char dest_path[200];
            snprintf(dest_path, sizeof(dest_path), "%s/examen.pdf", student_dir);

            // Crear un enlace simbólico del archivo de examen al directorio del estudiante
            if (link(exam_path, dest_path) == -1) {
                // Manejar el error si falla la creación del enlace simbólico
            }
        } else {
            // Mostrar un mensaje de error si el archivo de examen no existe
            fprintf(stderr, "El modelo de examen %s.pdf no existe.\n", exam_model);
            exit(EXIT_FAILURE);
        }
    }

    // Cerrar el archivo estudiantes.txt
    fclose(file);

    // Imprimir un mensaje de finalización
    printf("Proceso B terminado\n");

    exit(0);
}