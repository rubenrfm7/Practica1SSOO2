# Practica1SSOO2
Para ejecutar la practica ejecutar comando:
make

Esto compilara todos los archivos necesarios para su ejecución.

Ejecutamos el manager:

./manager

Esto ejecutara los procesos A,B,C y el proceso demonio

El proceso A creara los directorios de los estudiantes.

El proceso B añadira el examen correspondiente a cada estudiante en su directorio.

El proceso C añadira un archivo info.txt con la nota que necesita para superar la prueba.

El proceso demon hara un backup de todos los archivos y directorios del directorio donde nos encontremos, este mostrara por pantalla su pid para finalizarlo en caso necesario mediante:

kill "pid"

El manager cuando finaliza sus procesos A,B y C duerme durante 6 segundos, lo que nos dejara tiempo para ejecutar CRTL+C y ejecutar el proceso D

El proceso D borrara todos los directorios creados por el proceso A.

