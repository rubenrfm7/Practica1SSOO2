#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
int main() {
    while (1) {
        printf("Realizando copia de seguridad proceso DEMON...\n");
        char backup_dir[] = "../backup";
        mkdir(backup_dir, 0777);
        system("cp -r * ../backup");
        printf("Copia de seguridad completada.\n");
        sleep(60); 
    }
    return 0;
}