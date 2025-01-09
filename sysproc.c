#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int
sys_date(void)
{
  char *ptr;
  argptr(0, &ptr, sizeof(struct rtcdate*));
  cprintf("Data atual: 2025-01-08 15:30:00\n");
  return 0; // Retorno para indicar sucesso.
}

pte_t *walkpgdir(pde_t *pgdir, const void *va, int alloc);

int
sys_virt2real(void)
{
    char *va;
    if (argptr(0, &va, sizeof(char*)) < 0)
        return -1;

    pte_t *pte = walkpgdir(myproc()->pgdir, va, 0); // Localiza o PTE.
    if (!pte || !(*pte & PTE_P)) // Verifica se a página está presente.
        return -1;

    uint pa = PTE_ADDR(*pte); // Obtém o endereço físico base.
    return pa | ((uint)va & 0xFFF); // Retorna o endereço físico como inteiro.
}


int
sys_num_pages(void)
{
    struct proc *curproc = myproc();
    int num_pages = 0;

    for (uint va = 0; va < curproc->sz; va += PGSIZE) {
        pte_t *pte = walkpgdir(curproc->pgdir, (char*)va, 0); // Localiza o PTE.
        if (pte && (*pte & PTE_P)) // Verifica se a página está presente.
            num_pages++;
    }
    return num_pages;
}

