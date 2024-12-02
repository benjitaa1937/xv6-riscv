#include "types.h"
#include "param.h"
#include "spinlock.h"
#include "proc.h"
#include "msg.h"
#include "defs.h"

struct msgqueue mqueue;  // Definición global de la cola de mensajes

void
msg_init(void)
{
  initlock(&mqueue.lock, "msgqueue");
  mqueue.head = 0;
  mqueue.tail = 0;
  mqueue.size = 0;
}

