#include "syslib.h"

/*===========================================================================*
 *                                sys_nice			     	     *
 *===========================================================================*/
PUBLIC int sys_insert(int proc, int prio)
{
  message m;

  m.m1_i1 = proc;
  m.m1_i2 = prio;
  return(_taskcall(SYSTASK, SYS_INSERT, &m));
}
