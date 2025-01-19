#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/prctl.h>
#include <err.h>

int
main() {
	if (prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0) == -1)
		err(1, "prctl PR_SET_NO_NEW_PRIVS");

	int rc = prctl(PR_GET_NO_NEW_PRIVS, 0, 0, 0, 0);
	if (rc == -1)
		err(1, "prctl PR_GET_NO_NEW_PRIVS");
	else if (!rc)
		printf("PASS\n");
	else
		exit(1);

	return (0);
}
