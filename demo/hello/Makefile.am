pkglib_LTLIBRARIES = hello.la

hello_la_SOURCES = \
	hello.ecpp \
	tntnet.png

AM_CPPFLAGS = -I$(top_srcdir)/framework/common
hello_la_LDFLAGS = -module @SHARED_LIB_FLAG@
hello_la_LIBADD = $(top_builddir)/framework/common/libtntnet.la

noinst_DATA = tntnet.xml
dist_noinst_DATA = README
CLEANFILES = hello.cpp tntnet.cpp tntnet.xml

ECPPC=$(top_builddir)/sdk/tools/ecppc/ecppc

SUFFIXES=.ecpp .png .cpp
.ecpp.cpp:
	$(AM_V_GEN)$(ECPPC) -o $@ $<
.png.cpp:
	$(AM_V_GEN)$(ECPPC) -b -m image/png -o $@ $<

tntnet.xml:
	$(AM_V_GEN)$(SHELL) $(top_builddir)/misc/tntnet-project --config=hello|$(AWK) '/<\/tntnet>/{print "  <compPath>\n    <entry>.libs</entry>\n  </compPath>"} {print}' >$@
