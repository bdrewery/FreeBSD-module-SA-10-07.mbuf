// bryan
// Thanks to http://www.packetstormsecurity.org/papers/unix/bsdkern.htm
#include <sys/types.h>
#include <sys/param.h>
#include <sys/proc.h>
#include <sys/module.h>
#include <sys/sysent.h>
#include <sys/kernel.h>
#include <sys/systm.h>
#include <sys/linker.h>
#include <sys/sysproto.h>
#include <sys/sysent.h>
#include <sys/proc.h>
#include <sys/syscall.h>


/*The blocked system call*/
static int
blocked_sendfile(struct thread *td, void *uap)
{      
 printf("BLOCKED SENDFILE(2) uid(%d) pid(%d) ppid(%d)\n", td->td_ucred->cr_uid, td->td_proc->p_pid, td->td_proc->p_pptr->p_pid);
 return EINVAL;
}

/*our load function*/
static int
dummy_handler (struct module *module, int cmd, void *arg)
{
 int error = 0;

 switch (cmd) {
  case MOD_LOAD :
   sysent[SYS_sendfile].sy_call=(sy_call_t*)blocked_sendfile;
   sysent[SYS_sendfile].sy_narg = 7;
  break;
  case MOD_UNLOAD :
   sysent[SYS_sendfile].sy_call=(sy_call_t*)sendfile;
  break;
  default :
   error = EINVAL;
  break;
 }
 return error;
}
  
static moduledata_t syscall_mod = {
 "SA-10:07.mbuf",
 dummy_handler,
 NULL
};

DECLARE_MODULE(syscall, syscall_mod, SI_SUB_DRIVERS, SI_ORDER_MIDDLE);
