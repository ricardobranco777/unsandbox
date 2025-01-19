#define _GNU_SOURCE
#include <stdio.h>
#include <dlfcn.h>
#include <sys/syscall.h>
#include <linux/capability.h>
#include <err.h>

typedef int (*syscall_t)(long, ...);

long
syscall(long number, ...) {
	static syscall_t real_syscall = NULL;

	if (!real_syscall) {
		real_syscall = (syscall_t)dlsym(RTLD_NEXT, "syscall");
		if (!real_syscall)
			err(1, "syscall: %s", dlerror());
	}

	switch (number) {
		/* XXX Shall we add SYS_capget? */
		case SYS_capset:
#ifdef SYS_landlock_restrict_self
		case SYS_landlock_restrict_self:
#endif
			return (0);
#if 0
		case SYS_getuid:
			return (777);
#endif
		default:
			break;
	}

	/*
	 * This only works on GCC:
	 * https://gcc.gnu.org/onlinedocs/gcc/Constructing-Calls.html
	 */
	void *args = __builtin_apply_args();
	void *ret = __builtin_apply((void *)real_syscall, args, 100);

	__builtin_return(ret);
}
