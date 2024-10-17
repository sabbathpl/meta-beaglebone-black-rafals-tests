AUTOMAKE_OPTIONS = foreign

include_HEADERS = ssd1306.h

# Shared lib
lib_LTLIBRARIES = liboleddisplay.la

# Static lib
lib_LIBRARIES = liboleddisplay.a

SOURCES = \
    ssd1306.c \
    linux_i2c.c

liboleddisplay_la_SOURCES = $(SOURCES)
liboleddisplay_a_SOURCES = $(SOURCES)

liboleddisplay_la_CFLAGS = -Wall -Werror -fPIC
liboleddisplay_la_LDFLAGS = -shared

liboleddisplay_a_CFLAGS = -Wall -Werror -fPIC
liboleddisplay_a_LDFLAGS = -static
ACLOCAL_AMFLAGS = -I m4
