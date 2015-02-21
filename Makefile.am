SUBDIRS=

lib_LTLIBRARIES      = libaducid.la libaducidpp.la

libaducid_la_SOURCES = \
    src/aducid.c \
    src/aducidsoap.c \
    src/attrlist.c \
    src/httpclient.c \
    src/myxml.c \
    src/peig.c \
    src/soap.c \
    src/utils.c

libaducid_la_LDFLAGS=-version-info 3:0:0 -lcurl
libaducid_la_CFLAGS = -shared


libaducidpp_la_SOURCES = \
    src/aducid++.cc

libaducidpp_la_LDFLAGS = -L$(builddir)/.libs -laducid -lcurl -version-info 3:0:0
libaducidpp_la_CPPFLAGS = -shared -I$(srcdir)/src
libaducidpp_la_CFLAGS = -shared -I$(srcdir)/src

