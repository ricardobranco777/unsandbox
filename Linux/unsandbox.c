#define _GNU_SOURCE
#include <stdio.h>
#include <dlfcn.h>
#include <sys/prctl.h>
#include <err.h>

typedef int (*prctl_t)(int, ...);

/*
 * XXX This call may be redirected by Glibc to __prctl_time64
 */
int
prctl(int op, ...)
{
	static prctl_t real_prctl = NULL;

	if (real_prctl == NULL) {
		real_prctl = (prctl_t)dlsym(RTLD_NEXT, "prctl");
		if (real_prctl == NULL)
			errx(1, "dlsym: %s", dlerror());
	}

	/*
	 * https://www.kernel.org/doc/Documentation/prctl/no_new_privs.txt
	 * https://www.kernel.org/doc/Documentation/prctl/seccomp_filter.txt
	 */
	switch (op) {
		/* XXX Shall we add PR_CAPBSET_READ? */
		case PR_CAPBSET_DROP:
		/*
		 * XXX Shall we add the GET versions of these?
		 */
		case PR_SET_NO_NEW_PRIVS:
		case PR_SET_SECCOMP:
			return (0);
		default:
			break;
	}

	/*
	 * This only works on GCC:
	 * https://gcc.gnu.org/onlinedocs/gcc/Constructing-Calls.html
	 */
	void *args = __builtin_apply_args();
	void *ret = __builtin_apply((void *)real_prctl, args, 100);

	__builtin_return(ret);
}
