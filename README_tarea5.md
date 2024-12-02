Tarea 5 Voluntaria - Benjamín González - IPC + Cola de mensajes

La tarea fue complicada, obtuve muchos erroes en el camino referente a la definición de estructuras, entre otros y
hubo algunos que no fui capaz de resolver, sin embargo, considero que la mayoría del trabajo fue correcto.Tuve errores
también dado que se me olvidaba modificar ciertos archivos, incluir otros y problemas con definiciones, pero esos
fui capaz de solucionar. Fue una buena experiencia trabajar en esta tarea para aprender cómo funcionan los IPC
a pesar de que el resultado no fue bueno, estoy seguro que me faltó un cambio mínimo para asegurar el funcionamiento. 
El IPC
debería permitir a los procesos de un sistema operativo comunicarse entre sí, en este caso, se utiliza una cola de 
mensajes.

Los pasos seguidos fueron: 
Crear un archivo msg.h, msg.c, modificar el sysproc.c, syscall.c, defs.h y crear el programa de prueba msg_test.c 
y agregarlo al makefile y finalmente modificar usys.pl para generar los stubs de las syscalls.


Los errores iban siendo solucionados pero aparecían otros, estos fueron los finales:
kernel/spinlock.h:2:8: error: redefinition of 'struct spinlock'
    2 | struct spinlock {
      |        ^~~~~~~~
In file included from kernel/sysproc.c:6:
kernel/spinlock.h:2:8: note: originally defined here
    2 | struct spinlock {
      |        ^~~~~~~~
kernel/sysproc.c: In function 'sys_send':
kernel/sysproc.c:135:11: error: passing argument 1 of 'acquire' from incompatible pointer type [-Werror=incompatible-pointer-types]
  135 |   acquire(&mqueue.lock);
      |           ^~~~~~~~~~~~
      |           |
      |           struct spinlock *
In file included from kernel/sysproc.c:3:
kernel/defs.h:113:25: note: expected 'struct spinlock *' but argument is of type 'struct spinlock *'
  113 | void            acquire(struct spinlock*);
      |                         ^~~~~~~~~~~~~~~~
kernel/sysproc.c:138:13: error: passing argument 1 of 'release' from incompatible pointer type [-Werror=incompatible-pointer-types]
  138 |     release(&mqueue.lock);
      |             ^~~~~~~~~~~~
      |             |
      |             struct spinlock *
kernel/defs.h:116:25: note: expected 'struct spinlock *' but argument is of type 'struct spinlock *'
  116 | void            release(struct spinlock*);
      |                         ^~~~~~~~~~~~~~~~
kernel/sysproc.c:149:11: error: passing argument 1 of 'release' from incompatible pointer type [-Werror=incompatible-pointer-types]
  149 |   release(&mqueue.lock);
      |           ^~~~~~~~~~~~
      |           |
      |           struct spinlock *
kernel/defs.h:116:25: note: expected 'struct spinlock *' but argument is of type 'struct spinlock *'
  116 | void            release(struct spinlock*);
      |                         ^~~~~~~~~~~~~~~~
kernel/sysproc.c: In function 'sys_receive':
kernel/sysproc.c:160:6: error: void value not ignored as it ought to be
  160 |   if(argaddr(0, &addr) < 0)
      |      ^~~~~~~~~~~~~~~~~
kernel/sysproc.c:165:11: error: passing argument 1 of 'acquire' from incompatible pointer type [-Werror=incompatible-pointer-types]
  165 |   acquire(&mqueue.lock);
      |           ^~~~~~~~~~~~
      |           |
      |           struct spinlock *
kernel/defs.h:113:25: note: expected 'struct spinlock *' but argument is of type 'struct spinlock *'
  113 | void            acquire(struct spinlock*);
      |                         ^~~~~~~~~~~~~~~~
kernel/sysproc.c:168:20: error: passing argument 2 of 'sleep' from incompatible pointer type [-Werror=incompatible-pointer-types]
  168 |     sleep(&mqueue, &mqueue.lock);
      |                    ^~~~~~~~~~~~
      |                    |
      |                    struct spinlock *
kernel/defs.h:100:30: note: expected 'struct spinlock *' but argument is of type 'struct spinlock *'
  100 | void            sleep(void*, struct spinlock*);
      |                              ^~~~~~~~~~~~~~~~
kernel/sysproc.c:173:13: error: passing argument 1 of 'release' from incompatible pointer type [-Werror=incompatible-pointer-types]
  173 |     release(&mqueue.lock);
      |             ^~~~~~~~~~~~
      |             |
      |             struct spinlock *
kernel/defs.h:116:25: note: expected 'struct spinlock *' but argument is of type 'struct spinlock *'
  116 | void            release(struct spinlock*);
      |                         ^~~~~~~~~~~~~~~~
kernel/sysproc.c:180:11: error: passing argument 1 of 'release' from incompatible pointer type [-Werror=incompatible-pointer-types]
  180 |   release(&mqueue.lock);
      |           ^~~~~~~~~~~~
      |           |
      |           struct spinlock *
kernel/defs.h:116:25: note: expected 'struct spinlock *' but argument is of type 'struct spinlock *'
  116 | void            release(struct spinlock*);
