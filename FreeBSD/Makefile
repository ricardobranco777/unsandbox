SHLIB_NAME= libunsandbox.so
SRCS=   unsandbox.c

WITHOUT_DEBUG_FILES=
CLEANFILES+=	test test.o

.include <bsd.lib.mk>

test:  $(SHLIB_NAME)
	$(MAKE) -f Makefile.test

.PHONY: testit
testit:	test $(SHLIB_NAME)
	$(MAKE) -f Makefile.test testit
