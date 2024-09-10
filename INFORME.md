Informe Tarea 1
Benjamín González

Las llamadas al sistema consisten en herramientas o procedimiento proporcionado por el sistema operativo para permitir
que los programas interactúen con los recursos del sistema, tales como la memoria, dispositivos de entrada y
salida, procesador, entre otros. Se evita acceder directamente al hardware, las llamadas son intermediadas
a través del kernel del sistema operativo. Básicamente, las llamadas al sistema se llevan a cabo cuando un programa
requiere permisos especiales para operaciones que involucren al sistema operativo y están protegidas, solo pudiendo
ser ejecutadas de manera directa por el susodicho sistema operativo.
La función getppid(), consiste en una llamada al sistema que retorna el PID (Process ID) del proceso padre del proceso 
que la invoca, siendo el proceso padre el que crea a otro proceso.
Para el desarrollo de esta tarea, no fue necesario crear programas de prueba, simplemente se implementó la función
getppid siguiendo los pasos del PPT y las instrucciones de la tarea. En resumen, se define syscall.h, se implementa
la función sys_getppid() en sysproc.c, se agrega la misma función a syscall.c, se declara la función en user.h y
se agrega una entrada para la función en usys.pl, por último, se modifica el Makefile para permitir la compilación
y ejecución correcta de la función. Con respecto a las dificultades, no hubo muchas considerando la tarea completa,
solo una mala optimización de tiempos y complicaciones con la Tarea 0 que me hicieron demorarme mucho en poder 
ejecutar xv6 por lo que no pude optar para el 7.0 en esta entrega, sin embargo, pretendo realizar igual la parte
de la entrega para maximizar mi aprendizaje.
