#ifndef MSG_H
#define MSG_H

#include "types.h"
#include "spinlock.h"

#define MAX_MESSAGES 64
#define MSG_SIZE 128

struct message {
  int sender_pid;
  char content[MSG_SIZE];
};

struct msgqueue {
  struct spinlock lock;
  struct message messages[MAX_MESSAGES];
  int head;
  int tail;
  int size;
};

extern struct msgqueue mqueue;
void msg_init(void);

#endif // MSG_H
