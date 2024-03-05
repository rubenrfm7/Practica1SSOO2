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


void signal_handler(int sig) {
    if (sig == SIGINT) {
        printf("Se recibió la señal SIGINT (Ctrl + C).\n");
        pid_t pd_pid = fork();
        if (pd_pid == 0) {
        execl("./pd","pd",NULL);
        perror("execl"); 
        exit(EXIT_FAILURE);
        } else if (pd_pid < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else {
            waitpid(pd_pid, NULL, 0);
            kill(0, SIGTERM); 
        }
    }
}


int main() {
    signal(SIGINT, signal_handler);
    pid_t pa_pid, pb_pid, pc_pid,demon_pid;
    int tuberia[2];
    char wr_tuberia[256];
    pipe(tuberia);
    sprintf(wr_tuberia,"%d",tuberia[1]);
    sleep(6);
    int status;
    demon_pid = fork();

    if (demon_pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (demon_pid == 0) {
        execl("./demon","demon",NULL);
        perror("execl"); 
    } else {
        
        printf("Proceso demonio creado con PID: %d\n", demon_pid);

    pa_pid = fork();
    
    if (pa_pid == 0) {
        execl("./pa","pa",NULL);
        perror("execl"); 
        exit(EXIT_FAILURE);
    }
    else if (pa_pid < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        } 
    else {
        waitpid(pa_pid,NULL,0);
    
        pb_pid = fork();
        if (pb_pid == 0) {
            execl("./pb","pb",NULL);
            perror("execl"); 
            exit(EXIT_FAILURE);
        }else if (pb_pid < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        } 
         else {
            pc_pid = fork();
            if (pc_pid == 0) {
                execl("./pc",wr_tuberia,NULL);
                perror("execl"); 
                exit(EXIT_FAILURE);
            }
            else if (pc_pid < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        } 
             else {
                waitpid(pb_pid, NULL, 0);
                waitpid(pc_pid, NULL, 0);
                close(tuberia[1]);
                char buffer[20];
                read(tuberia[0], buffer, sizeof(buffer));
                float nota_media = atof(buffer);
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
                    perror("fopen");
                }
                printf("FIN DE PROGRAMA\n");
            }
        }
        sleep(6);
        return 0;
        }
    }
}