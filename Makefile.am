DIST_SUBDIRS = m4 t

# EXTRA_DIST = jd_path.h jd_utf8.h

SUBDIRS = . t

ACLOCAL_AMFLAGS = -I m4

lib_LTLIBRARIES = libdynatron.la

include_HEADERS = dynatron.h

bin_PROGRAMS = dynatron

libdynatron_la_SOURCES = dynatron.h utils.h dy_core.c \
	dy_despatch.c dy_dummy.c dy_io.c dy_listener.c \
	dy_log.c dy_main.c dy_message.c dy_object.c \
	dy_queue.c dy_thread.c utils.c

libdynatron_la_LDFLAGS = -avoid-version

dynatron_SOURCES = dynatron.c

dynatron_LDADD = libdynatron.la

test: all
	cd t && $(MAKE) test

