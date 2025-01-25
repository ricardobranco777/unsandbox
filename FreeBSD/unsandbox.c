#include <errno.h>

#define	ERR_ENOSYS(func) \
int func(void)		\
{			\
	errno = ENOSYS;	\
	return (-1);	\
}

ERR_ENOSYS(cap_enter)
ERR_ENOSYS(cap_rights_limit)
ERR_ENOSYS(cap_fcntls_limit)
ERR_ENOSYS(cap_ioctls_limit)
