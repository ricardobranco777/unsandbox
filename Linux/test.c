#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <err.h>
#include <sys/prctl.h>
#include <sys/syscall.h>
#include <linux/seccomp.h>

#define USAGE	"Usage: %s seccomp1|seccomp2|privs"

static void
test_no_new_privs(void)
{
	int rc;

	if (prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0) == -1)
		err(1, "prctl PR_SET_NO_NEW_PRIVS");

	if ((rc = prctl(PR_GET_NO_NEW_PRIVS, 0, 0, 0, 0)) == -1)
		err(1, "prctl PR_GET_NO_NEW_PRIVS");
	else if (!rc)
		errx(1, "FAIL: no_new_privs");
}

static void
test_seccomp1(void)
{
	if (prctl(PR_SET_SECCOMP, SECCOMP_MODE_STRICT) == -1)
		err(1, "prctl");
}

static void
test_seccomp2(void)
{
	if (syscall(SYS_seccomp, SECCOMP_SET_MODE_STRICT, 0, NULL) == -1)
		err(1, "syscall");
}

int
main(int argc, char *argv[])
{
	if (!**argv || argc != 2)
		errx(1, USAGE, argv[0]);
	if (!strcmp(argv[1], "no_new_privs"))
		test_no_new_privs();
	else if (!strcmp(argv[1], "seccomp1"))
		test_seccomp1();
	else if (!strcmp(argv[1], "seccomp2"))
		test_seccomp2();
	else
		errx(1, USAGE, argv[0]);

	// This call needs access to /etc/passwd
	if (getpwuid(geteuid()) == NULL)
		err(1, "getpwuid");
	else
		printf("PASS: %s\n", argv[1]);

	return (0);
}
