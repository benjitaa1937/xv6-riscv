#include "kernel/types.h"
#include "user/user.h"

int
main(void)
{
  int pid = fork();
  
  if(pid < 0) {
    printf("fork failed\n");
    exit(1);
  }
  
  if(pid == 0) {  // proceso hijo (lector)
    char msg[128];
    while(1) {
      if(receive(msg) < 0) {
        printf("receive failed\n");
        exit(1);
      }
      printf("Received: %s\n", msg);
    }
  } else {  // proceso padre (escritor)
    char *messages[] = {
      "Hello",
      "World",
      "Testing",
      "IPC"
    };
    
    for(int i = 0; i < 4; i++) {
      if(send(messages[i]) < 0) {
        printf("send failed\n");
        exit(1);
      }
      sleep(1);  // pequeña pausa entre mensajes
    }
    
    wait(0);  // esperar al proceso hijo
  }
  
  exit(0);
}
