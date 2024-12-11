AUTOMAKE_OPTIONS = foreign

include_HEADERS = pi4ioe5v64xx.h

# Shared lib
lib_LTLIBRARIES = libpi4ioe5v64xx.la

# Static lib
# lib_LIBRARIES = libpi4ioe5v64xx.a

SOURCES = \
    i2c.cpp \
    pi4ioe5v64xx.cpp

libpi4ioe5v64xx_la_SOURCES = $(SOURCES)
# libpi4ioe5v64xx_a_SOURCES = $(SOURCES)

libpi4ioe5v64xx_la_CFLAGS = -Wall -Werror -fPIC
libpi4ioe5v64xx_la_LDFLAGS = -shared

# libpi4ioe5v64xx_a_CFLAGS = -Wall -Werror -fPIC
# libpi4ioe5v64xx_a_LDFLAGS = -static

ACLOCAL_AMFLAGS = -I m4