#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"
#include "msg.h"

uint64
sys_exit(void)
{
  int n;
  argint(0, &n);
  exit(n);
  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  argaddr(0, &p);
  return wait(p);
}

uint64
sys_sbrk(void)
{
  uint64 addr;
  int n;

  argint(0, &n);
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;

  argint(0, &n);
  if(n < 0)
    n = 0;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(killed(myproc())){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  argint(0, &pid);
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
uint64
sys_getppid(void)
{
    return myproc()->parent->pid;
}

uint64
sys_mprotect(void)
{
  uint64 addr;
  int len;
  
  // Obtener los argumentos de la syscall
  argaddr(0, &addr);
  argint(1, &len);
  
  return mprotect((void*)addr, len);
}

uint64
sys_munprotect(void)
{
  uint64 addr;  
  int len;
  
  // Obtener los argumentos de la syscall
  argaddr(0, &addr);
  argint(1, &len);
  
  return munprotect((void*)addr, len);
}
uint64
sys_send(void)
{
  char msg[MSG_SIZE];
  struct proc *p = myproc();

  if(argstr(0, msg, MSG_SIZE) < 0)
    return -1;

  acquire(&mqueue.lock);

  if(mqueue.size >= MAX_MESSAGES) {
    release(&mqueue.lock);
    return -1;
  }

  mqueue.messages[mqueue.tail].sender_pid = p->pid;
  safestrcpy(mqueue.messages[mqueue.tail].content, msg, MSG_SIZE);

  mqueue.tail = (mqueue.tail + 1) % MAX_MESSAGES;
  mqueue.size++;

  wakeup(&mqueue);
  release(&mqueue.lock);
  return 0;
}

uint64
sys_receive(void)
{
  char *msg;
  uint64 addr;
  struct proc *p = myproc();

  if(argaddr(0, &addr) < 0)
    return -1;
  
  msg = (char*)addr;

  acquire(&mqueue.lock);

  while(mqueue.size == 0) {
    sleep(&mqueue, &mqueue.lock);
  }

  if(copyout(p->pagetable, (uint64)msg, 
             mqueue.messages[mqueue.head].content, MSG_SIZE) < 0) {
    release(&mqueue.lock);
    return -1;
  }

  mqueue.head = (mqueue.head + 1) % MAX_MESSAGES;
  mqueue.size--;

  release(&mqueue.lock);
  return 0;
}

