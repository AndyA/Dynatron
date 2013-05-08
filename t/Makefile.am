TESTBIN = basic queue

TESTPERL = listen.t

EXTRA_DIST = commands.json

noinst_PROGRAMS = $(TESTBIN)

noinst_LTLIBRARIES = libtest-support.la

libtest_support_la_SOURCES = tap.c tap.h util.c util.h jd_test.c jd_test.h
libtest_support_la_LDFLAGS = -static

LDADD = libtest-support.la ../libdynatron.la

test-c: $(TESTBIN)
	prove -e '' $(addprefix ./,$(TESTBIN))

test-perl: $(TESTPERL)
	prove $(TESTPERL)

test: test-c test-perl

valgrind: $(TESTBIN)
	prove -e 'valgrind -q' $(addprefix ./,$(TESTBIN))
