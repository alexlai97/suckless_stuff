# slmenu version
VERSION = 0.1

# paths
PREFIX = /home/alex
MANPREFIX = ${PREFIX}/share/man

# flags
CPPFLAGS = -D_BSD_SOURCE -DVERSION=\"${VERSION}\"
CFLAGS   = -ansi -pedantic -Wall -Os ${CPPFLAGS}
LDFLAGS  = -s

# compiler and linker
CC = cc
