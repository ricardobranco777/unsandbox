#include <errno.h>

int
cap_enter(void)
{
	errno = ENOSYS;
	return (-1);
}

int
cap_rights_limit(void)
{
	errno = ENOSYS;
	return (-1);
}

int
cap_fcntls_limit(void)
{
	errno = ENOSYS;
	return (-1);
}

int
cap_ioctls_limit(void)
{
	errno = ENOSYS;
	return (-1);
}
