#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main() {
  int i;

  for(i = 0; i < 20; i++) {
    if(fork() == 0) {
      // Proceso hijo
      printf("Ejecutando proceso %d %d\n", i, getpid());
      sleep(10);  // Simula trabajo con un sleep de 10 ticks
      exit(0);    // Termina el proceso
    }
  }

  // El proceso padre espera que todos los hijos terminen
  for(i = 0; i < 20; i++) {
    wait(0);
  }

  exit(0);
}
