#include <stdio.h>
#include <unistd.h>
#include <err.h>

int
main(void) {
	// No promises made!
	if (pledge("", NULL) < 0)
		err(1, "pledge");
	printf("PASS\n");
}
