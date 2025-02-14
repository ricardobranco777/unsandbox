#define _GNU_SOURCE
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <err.h>
#include <sys/prctl.h>
#include <sys/syscall.h>
#include <linux/seccomp.h>
#include <linux/landlock.h>

#define USAGE	"Usage: %s landlock|no_new_privs|seccomp1|seccomp2"

static void
test_no_new_privs(void)
{
	int rc;

	if (prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0) == -1)
		err(1, "prctl PR_SET_NO_NEW_PRIVS");

	if ((rc = prctl(PR_GET_NO_NEW_PRIVS, 0, 0, 0, 0)) == -1)
		err(1, "prctl PR_GET_NO_NEW_PRIVS");

	if (rc != 0)
		errx(1, "PR_GET_NO_NEW_PRIVS: %d", rc);
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

static void
test_landlock(void)
{
	struct landlock_ruleset_attr ruleset_attr = {
		.handled_access_fs = LANDLOCK_ACCESS_FS_READ_FILE | LANDLOCK_ACCESS_FS_READ_DIR,
	};
	int fd;

	fd = syscall(SYS_landlock_create_ruleset, &ruleset_attr, sizeof(ruleset_attr), 0);
#if 0
	if (fd == -1)
		err(1, "landlock_create_ruleset");
#endif

	// Restrict access to an empty set of paths
	if (syscall(SYS_landlock_restrict_self, fd, 0) == -1)
		err(1, "landlock_restrict_self");

	(void)close(fd);
}

int
main(int argc, char *argv[])
{
	if (!**argv || argc != 2)
		errx(1, USAGE, argv[0]);
	if (!strcmp(argv[1], "landlock"))
		test_landlock();
	else if (!strcmp(argv[1], "seccomp1"))
		test_seccomp1();
	else if (!strcmp(argv[1], "seccomp2"))
		test_seccomp2();
	else if (!strcmp(argv[1], "no_new_privs")) {
		test_no_new_privs();
		printf("PASS: no_new_privs\n");
		return (0);
	} else
		errx(1, USAGE, argv[0]);

	// This call needs access to /etc/passwd
	if (getpwuid(geteuid()) == NULL)
		err(1, "getpwuid");
	else
		printf("PASS: %s\n", argv[1]);

	return (0);
}
