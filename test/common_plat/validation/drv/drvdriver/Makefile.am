include ../Makefile.inc

noinst_LTLIBRARIES = libtestdrvdriver.la
libtestdrvdriver_la_SOURCES = drvdriver.c

test_PROGRAMS = drvdriver_main$(EXEEXT)
dist_drvdriver_main_SOURCES = drvdriver_main.c
drvdriver_main_LDADD = libtestdrvdriver.la $(LIBCUNIT_COMMON) $(LIBODP)

EXTRA_DIST = drvdriver.h
