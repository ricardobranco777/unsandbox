#include <stdio.h>
#include <sys/capsicum.h>
#include <err.h>

int
main(void) {
	u_int mode;

	if (cap_enter() < 0)
		err(1, "cap_enter");
	/* XXX Shall we hijack this one too? */
	if (cap_getmode(&mode) < 0)
		err(1, "cap_getmode");
	if (mode)
		errx(1, "Inside sandbox");
	else
		printf("PASS\n");

	return (0);
}
