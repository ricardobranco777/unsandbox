CFLAGS	:= -Wall -Wextra -fPIC
LDFLAGS	:= -shared
LIB	:= libunsandbox.so

CLEANFILES = *.so *.o a.out test

$(LIB): unsandbox.c syscall.c lib.c
	$(LINK.c) $^ -o $@

.PHONY: clean
clean:
	$(RM) $(CLEANFILES)

test:	$(LIB)
	$(MAKE) -f Makefile.test

.PHONY: testit
testit:	test $(LIB)
	$(MAKE) -f Makefile.test testit
