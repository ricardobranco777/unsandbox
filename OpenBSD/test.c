#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <err.h>
#include <pwd.h>

#define USAGE	"Usage: %s pledge|unveil"

static void
test_pledge(void)
{
	// No promises made!
	if (pledge("", NULL) < 0)
		err(1, "pledge");
	printf("PASS: pledge\n");
}

static void
test_unveil(void)
{
	// Limit all filesystem calls to current directory
	if (unveil(".", "r") < 0)
		err(1, "unveil");
	if (unveil(NULL, NULL) < 0)
		err(1, "unveil");
	// This call needs access to /etc/passwd
	if (getpwuid(geteuid()) == NULL)
		err(1, "getpwuid");
	else
		printf("PASS: unveil\n");
}

int
main(int argc, char *argv[]) {
	if (!**argv || argc != 2)
		errx(1, USAGE, getprogname());
	if (!strcmp(argv[1], "pledge"))
		test_pledge();
	else if (!strcmp(argv[1], "unveil"))
		test_unveil();
	else
		errx(1, USAGE, getprogname());
}
