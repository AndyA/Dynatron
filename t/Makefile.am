TESTBIN = basic queue

TESTPERL = listen.t

EXTRA_DIST = commands.json

noinst_PROGRAMS = wrap $(TESTBIN)

noinst_LTLIBRARIES = libtest-support.la

libtest_support_la_SOURCES = tap.c tap.h util.c util.h jd_test.c jd_test.h
libtest_support_la_LDFLAGS = -static

LDADD = libtest-support.la ../libdynatron.la

wrap_LDADD =

test: $(TESTBIN)
	prove -e ./wrap $(TESTBIN) $(TESTPERL)

valgrind: $(TESTBIN)
	prove -e 'valgrind -q' $(addprefix ./,$(TESTBIN))
