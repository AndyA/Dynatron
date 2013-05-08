TESTBIN = basic

EXTRA_DIST = commands.json

noinst_PROGRAMS = $(TESTBIN)

noinst_LTLIBRARIES = libtest-support.la

libtest_support_la_SOURCES = tap.c tap.h util.c util.h jd_test.c jd_test.h
libtest_support_la_LDFLAGS = -static

LDADD = libtest-support.la ../libdynatron.la

test: $(noinst_PROGRAMS)
	prove -e '' $(addprefix ./,$(noinst_PROGRAMS))

valgrind: $(noinst_PROGRAMS)
	prove -e 'valgrind -q' $(addprefix ./,$(noinst_PROGRAMS))
