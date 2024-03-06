#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    // Mensaje indicando el comienzo del proceso C
    printf("El proceso C calculando notas necesarias para superar la prueba\n");
    
    // Abrir el archivo de texto "estudiantes.txt" en modo lectura
    FILE *file = fopen("estudiantes.txt", "r");
    if (file == NULL) {
        // Manejar el error si no se puede abrir el archivo
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    
    // Declarar variables para almacenar el número total de estudiantes y la suma de notas
    int nestudiantes = 0;
    int sumadenotas = 0;
    
    // Declarar un array para almacenar cada línea del archivo
    char line[100];
    
    // Leer el archivo línea por línea
    while (fgets(line, sizeof(line), file)) {
        char dni[20], exam_model[2];
        int nota_primera_prueba;
        
        // Analizar la línea para extraer el DNI del estudiante, el modelo de examen y la nota de la primera prueba
        sscanf(line, "%s %s %d", dni, exam_model, &nota_primera_prueba);
        
        // Crear la ruta del directorio del estudiante
        char student_dir[100];
        snprintf(student_dir, sizeof(student_dir), "%s", dni);
        
        // Calcular la nota necesaria para superar la prueba
        float nota_necesaria = (5.0 + nota_primera_prueba) / 2;
        
        // Crear un mensaje con la nota necesaria
        char mensaje[100];
        snprintf(mensaje, sizeof(mensaje), "La nota que debes obtener en este nuevo examen para superar la prueba es %.2f.", nota_necesaria);
        
        // Crear la ruta del archivo "info.txt" en el directorio del estudiante
        char estudiante_info_path[200];
        snprintf(estudiante_info_path, sizeof(estudiante_info_path), "%s/info.txt", student_dir);
        
        // Abrir el archivo "info.txt" en modo escritura
        FILE *estudiante_info_file = fopen(estudiante_info_path, "w");
        if (estudiante_info_file != NULL) {
            // Escribir el mensaje en el archivo "info.txt"
            fprintf(estudiante_info_file, "%s\n", mensaje);
            fclose(estudiante_info_file);
        } else {
            // Manejar el error si no se puede abrir el archivo
            perror("fopen");
            exit(EXIT_FAILURE);
        }
        
        // Actualizar el número total de estudiantes y la suma de notas
        nestudiantes++;
        sumadenotas += nota_primera_prueba;
    }
    
    // Calcular la nota media de la clase
    float nota_media = (float)sumadenotas / nestudiantes;
    
    // Convertir la nota media en una cadena
    char buffer[20];
    snprintf(buffer, sizeof(buffer), "%.2f", nota_media);
    
    // Escribir la nota media en el descriptor de archivo proporcionado como argumento
    write(atoi(argv[0]), buffer, strlen(buffer) + 1);
    
    // Cerrar el archivo de texto
    fclose(file);
    
    // Mensaje indicando el final del proceso C
    printf("Proceso C terminado\n");
    
    exit(0);
}