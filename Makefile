OBJECTS=interface.c parse.c queue.c stack.c debug.c	arithmetics.c
TESTCHKSRC=tests.check
TESTSRC=tests.c
FLAGS=-lgtk-3 -lgdk-3 -lz -lpangocairo-1.0 -lpango-1.0 -lharfbuzz -latk-1.0 -lcairo-gobject -lcairo -lgdk_pixbuf-2.0 -lgio-2.0 -lgobject-2.0 -lglib-2.0 
INCLUDES=-I/usr/include/gtk-3.0 -I/usr/include/pango-1.0 -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/include/harfbuzz -I/usr/include/freetype2 -I/usr/include/libpng16 -I/usr/include/libmount -I/usr/include/blkid -I/usr/include/fribidi -I/usr/include/cairo -I/usr/include/pixman-1 -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/gio-unix-2.0 -I/usr/include/atk-1.0 -I/usr/include/at-spi2-atk/2.0 -I/usr/include/at-spi-2.0 -I/usr/include/dbus-1.0 -I/usr/lib/x86_64-linux-gnu/dbus-1.0/include

include build.mk

ifeq ($(OS), Darwin)
	PKGFLAGS=-lcheck
else
	CHECKFLAGS=-lcheck	-lpthread	-lpthread	-lrt	-lm	-lsubunit
endif

test:
	checkmk clean_mode=1 $(TESTCHKSRC) > $(TESTSRC)
	$(CC)	$(TESTSRC)	$(OBJECTS)	$(PKGFLAGS)	-o	TestsSmartCalc $(CHECKFLAGS)	--coverage $(FLAGS)	$(INCLUDES)

clear:
	rm -rf TestsSmartCalc*