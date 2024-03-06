#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>
#include <time.h>

#define MAX_BUFFER_SIZE 1024

// Función manejadora de la señal SIGINT CTRL+C
void signal_handler(int sig) {
    if (sig == SIGINT) {
        printf("Se recibió la señal SIGINT (Ctrl + C).\n");

        // Creamos el proceso pd
        pid_t pd_pid = fork();
        if (pd_pid == 0) {
            // En el proceso hijo, ejecutamos pd
            execl("./pd", "pd", NULL);
            perror("execl"); // En caso de error al ejecutar execl mostramos el error
            exit(EXIT_FAILURE);
        } else if (pd_pid < 0) {
            // Captuamos el error al crear el proceso D
            perror("fork");
            exit(EXIT_FAILURE);
        } else {
            // Esperar a que el proceso D termine y luego enviar una señal SIGTERM a todos los procesos en ejecucion
            waitpid(pd_pid, NULL, 0);
            kill(0, SIGTERM);
        }
    }
}

int main() {
    // Establecer el manejador de señales CTRL+C
    signal(SIGINT, signal_handler);

    // Declaración de variables para los PID de los procesos
    pid_t pa_pid, pb_pid, pc_pid, demon_pid;
    
    // Declaración de la tubería
    int tuberia[2];
    char wr_tuberia[256];

    // Creaamos la tubería
    pipe(tuberia);

    // Convertir el descriptor de archivo de la tubería a una cadena
    sprintf(wr_tuberia, "%d", tuberia[1]);

    //Creamos el proceso demon
    demon_pid = fork();

    if (demon_pid < 0) {
        // Capturamos el error al crear el proceso demonio
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (demon_pid == 0) {
        // En el proceso hijo, ejecutar "demon"
        execl("./demon", "demon", NULL);
        perror("execl");
    } else {
        // Mensaje indicando el PID del demonio para poder deterlo en caso necesario
        printf("Proceso demonio creado con PID: %d\n", demon_pid);

        // Creaamos el proceso "pa"
        pa_pid = fork();
        if (pa_pid == 0) {
            // En el proceso hijo, ejecutar "pa"
            execl("./pa", "pa", NULL);
            perror("execl");
            exit(EXIT_FAILURE);
        } else if (pa_pid < 0) {
            // Capturamos el error al crear el proceso hijo para "pa"
            perror("fork");
            exit(EXIT_FAILURE);
        } else {
            // Esperamos a que el proceso "pa" termine y luego crear el proceso "pb" y "pc"
            waitpid(pa_pid, NULL, 0);
            pb_pid = fork();
            if (pb_pid == 0) {
                // En el proceso hijo, ejecutar "pb"
                execl("./pb", "pb", NULL);
                perror("execl");
                exit(EXIT_FAILURE);
            } else if (pb_pid < 0) {
                // Error al crear el proceso hijo para "pb"
                perror("fork");
                exit(EXIT_FAILURE);
            } else {
                //Creamos el proceso "pc"
                pc_pid = fork();
                if (pc_pid == 0) {
                    // En el proceso hijo, ejecutar "pc" pasando el descriptor de archivo de la tubería como argumento
                    execl("./pc", wr_tuberia, NULL);
                    perror("execl");
                    exit(EXIT_FAILURE);
                } else if (pc_pid < 0) {
                    // Error al crear el proceso hijo para "pc"
                    perror("fork");
                    exit(EXIT_FAILURE);
                } else {
                    // Esperar a que los procesos "pb" y "pc" terminen
                    waitpid(pb_pid, NULL, 0);
                    waitpid(pc_pid, NULL, 0);

                    // Cerrar la escritura de la tubería y leer desde la lectura
                    close(tuberia[1]);
                    char buffer[20];
                    read(tuberia[0], buffer, sizeof(buffer));
                    float nota_media = atof(buffer);

                    // Abrir el archivo de log en modo anexion y escribir los resultados de la ejecución
                    FILE *log_file = fopen("log.txt", "a");
                    time_t current_time = time(NULL);
                    struct tm *local_time = localtime(&current_time);
                    if (log_file != NULL) {
                        fprintf(log_file, "Fecha y hora: %s", asctime(local_time));
                        fprintf(log_file, "******** Log del sistema ********\n");
                        fprintf(log_file, "Creación de directorios finalizada.\n");
                        fprintf(log_file, "Copia de modelos de examen, finalizada.\n");
                        fprintf(log_file, "Creación de archivos con nota necesaria para alcanzar la nota de corte, finalizada.\n");
                        fprintf(log_file, "La nota media de la clase es: %.2f\n", nota_media);
                        fprintf(log_file, "FIN DE PROGRAMA\n");
                        fclose(log_file);
                    } else {
                        // Capturamos el error al abrir el archivo de log
                        perror("fopen");
                    }

                    // Mensaje indicando el final del programa
                    printf("FIN DE PROGRAMA\n");
                }
            }
        }

        // Retardo de 6 segundos antes de finalizar el programa principal por si se quiere ejecutar alguna accion
        sleep(6);
        return 0;
    }
}