#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <err.h>
#include <pwd.h>
#include <priv.h>

int
main(void) {
	priv_set_t *empty_set;

	if ((empty_set = priv_allocset()) == NULL)
		err(1, "priv_allocset");

	priv_emptyset(empty_set);
	if (setppriv(PRIV_SET, PRIV_EFFECTIVE, empty_set) == -1)
		err(1, "setppriv");

	priv_freeset(empty_set);

	if (getpwuid(geteuid()) == NULL)
		err(1, "getpwuid");
	else
		printf("PASS\n");

	return (0);
}
