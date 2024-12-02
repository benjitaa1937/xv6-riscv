#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main() {
    if (fork() == 0) {
        // Proceso lector
        char buf[128];
        while (1) {
            if (sys_receive(buf) == 0) {
                printf("Recibido: %s\n", buf);
            }
        }
    } else {
        // Proceso escritor
        char *msgs[] = {"Mensaje 1", "Mensaje 2", "Mensaje 3"};
        for (int i = 0; i < 3; i++) {
            sys_send(msgs[i]);
            sleep(10);
        }
        wait(0);
    }
    exit(0);
}
