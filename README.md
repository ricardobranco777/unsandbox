
Disable sandbox via shared-library hijacking

Supported sandboxes:
  - FreeBSD [capsicum](https://man.freebsd.org/cgi/man.cgi?query=capsicum&sektion=4)
  - OpenBSD [pledge](https://man.openbsd.org/pledge)
  - Illumos [privileges](https://illumos.org/man/7/privileges)

## Usage

```
make
LD_PRELOAD=$PWD/$(uname -s)/libunsandbox.so
```

See **ld.so**(8) manpage for alternatives to `LD_PRELOAD`

## BUGS / Limitations
  - Doesn't support statically compiled binaries
  - Doesn't support setuid/setgid binaries
