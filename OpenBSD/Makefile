LIB=	unsandbox
SRCS=   $(LIB).c

SHLIB_MAJOR=	0
SHLIB_MINOR=	0
NOLIBSTATIC=
CLEANFILES+=	lib$(LIB).so test test.o

# OpenBSD doesn't let us create unversioned shared-libraries
# so we hijack the main target to make a hard-link later
.MAIN: ALL
ALL: lib$(LIB).so

.include <bsd.lib.mk>

lib$(LIB).so: lib$(LIB).so.$(SHLIB_MAJOR).$(SHLIB_MINOR)
	ln lib$(LIB).so.$(SHLIB_MAJOR).$(SHLIB_MINOR) $@

test:	lib$(LIB).so
	$(MAKE) -f Makefile.test

.PHONY: testit
testit:	test lib$(LIB).so
	$(MAKE) -f Makefile.test testit
