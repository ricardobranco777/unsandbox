#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/capsicum.h>
#include <errno.h>
#include <err.h>

#define USAGE	"Usage: %s cap_enter|cap_rights_limit"

static void
test_cap_enter(void)
{
	u_int mode;

	if (cap_enter() < 0 && errno != ENOSYS)
		err(1, "cap_enter");
	if (cap_getmode(&mode) < 0)
		err(1, "cap_getmode");
	if (mode)
		errx(1, "Inside sandbox");
	else
		printf("PASS\n");
}

static void
test_cap_rights_limit(void)
{
	cap_rights_t rights;
	char buf[BUFSIZ];
	int fd;

	fd = open("/etc/passwd", O_RDONLY);
	if (fd == -1)
		err(1, "open");

	// No CAP_READ
	(void)cap_rights_init(&rights, CAP_FSTAT);

	if (cap_rights_limit(fd, &rights) == -1 && errno != ENOSYS)
		err(1, "cap_rights_limit");

	if (read(fd, buf, sizeof(buf)) == -1)
		err(1, "read");
	else
		printf("PASS\n");

	(void)close(fd);
}

int
main(int argc, char *argv[]) {
	if (!**argv || argc != 2)
		errx(1, USAGE, getprogname());
	if (!strcmp(argv[1], "cap_enter"))
		test_cap_enter();
	else if (!strcmp(argv[1], "cap_rights_limit"))
		test_cap_rights_limit();
	else
		errx(1, USAGE, getprogname());
}
