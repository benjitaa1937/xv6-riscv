Informe Tarea 0
Benjamín González

Pasos seguidos para instalar xv6:
1) Instalé WSL con Ubuntu, dado que trabajo en Windows.

2) Instalé múltiples dependencias, todo lo necesario (gcc, qemu, git, entre otros), aquí tuve el primer problema
en relación a QEMU que explicaré más adelante.

3) Cloné el repositorio de xv6-riscv del MIT.

4) Cloné el repositorio de xv6-gnu-toolchain (como mismo indica la página de xv6-riscv) y lo compilé, esto funcionó
bien y no tuve ningún problema con el toolchain.

5) Creé la branch en el repositorio clonado de xv6 "benjamin_gonzalez_t0".

6) Ahora intenté compilar xv6 pero tuve un problema que me costó mucho solucionar dado a que no sabía qué era porque
no había mensaje de error, lo que sucedía era que al ejectuar el comando "make qemu", se ejecutaba aparentemente
con éxito pero en la terminal no apareció nada más, se quedaba congelado, esto cuando utilizaba el modo "nographic",
si no usaba dicho modo, se abría la terminal qemu sin problemas pero no cargaba el xv6 (ningún mensaje de confirmación,
y los comandos no eran reconocidos).

7) Para solucionar lo anterior, intenté muchas alternativas diferentes, reinstalar todo (que se demoraba, por el tema
de compilar el toolchain), utilizar un computador diferente, pero me daba el mismo problema siempre, y ahí me fijé
en las versiones de QEMU y el toolchain y vi algo que me dio una idea de qué podía ser, la versión de qemu por alguna
razón se me instalaba siempre en 6.2.0, que es del 2021, mientras que el toolchain era del 2023 por lo que probé actualizando ubuntu completamente y reinstalando las dependencias, por lo que se actualizaron y de esta forma pude
finalmente ejecutar el xv6 correctamente, como se ve en las imágenes adjuntadas.

8) Ahora solo quedaba finalizar la tarea y subir todo a github, con commit, push y luego creando el fork respectivo,
en donde tuve mínimos problemas al intentar realizar el push en el repositorio oficial de xv6 donde evidentemente
no tenía permisos, por lo que creé el fork primero y subí todo ahí después.
