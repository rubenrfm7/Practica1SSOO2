#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
int main() {
    //En un bucle infinito mostramos por pantalla que se esta haciendo una copia de seguridad y copiamos todos los archivos del directorio 
    //donde nos encontramos en la carpeta backup que se encontrara en el directorio padre de donde nos encontremos
    while (1) {
        printf("Realizando copia de seguridad proceso DEMON...\n");
        char backup_dir[] = "../backup";
        mkdir(backup_dir, 0777);
        system("cp -r * ../backup");
        printf("Copia de seguridad completada.\n"); 
        //Dormimos 60 segundas para que se haga copia de seguridad 1 vez cada minuto
        sleep(60); 
    }
    return 0;
}