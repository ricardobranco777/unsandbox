OS :sh = uname

.PHONY: all clean

all:
	$(MAKE) -C $(OS)

clean:
	$(MAKE) -C $(OS) clean

testit:
	$(MAKE) -C $(OS) testit
