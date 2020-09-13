# dwm version
VERSION = 6.2

BUILD_TYPE ?= debug

# Customize below to fit your system

# paths
PREFIX = /usr/local
MANPREFIX = ${PREFIX}/share/man

X11INC = /usr/include
X11LIB = /usr/lib

# Xinerama, comment if you don't want it
XINERAMALIBS  = -lXinerama
XINERAMAFLAGS = -DXINERAMA

# freetype
FREETYPELIBS = -lfontconfig -lXft
FREETYPEINC = /usr/include/freetype2
#KVMLIB = -lkvm

# includes and libs
INCS = -I${X11INC} -I${FREETYPEINC}
LIBS = -L${X11LIB} -lX11 ${XINERAMALIBS} ${FREETYPELIBS} -lX11-xcb -lxcb -lxcb-res ${KVMLIB} -lXrender

# flags
CPPFLAGS = -D_DEFAULT_SOURCE -D_BSD_SOURCE -D_POSIX_C_SOURCE=200809L -DVERSION=\"${VERSION}\" ${XINERAMAFLAGS}
ifeq ($(BUILD_TYPE),debug)
	CFLAGS   = -g -std=c11 -pedantic -Wall -O0 ${INCS} ${CPPFLAGS}
else
	CFLAGS   = -std=c11 -Wall -Wno-deprecated-declarations -Os ${INCS} ${CPPFLAGS}
endif
LDFLAGS  = ${LIBS}

# Solaris
#CFLAGS = -fast ${INCS} -DVERSION=\"${VERSION}\"
#LDFLAGS = ${LIBS}

# compiler and linker
CC = gcc
