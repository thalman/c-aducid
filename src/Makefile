MINORVERSION=0
MAJORVERSION=3.0
VERSION=$(MAJORVERSION).$(MINORVERSION)

LD=ld
CC=gcc
CFLAGS=-Wall -g -fpic --pedantic -fvisibility=hidden `pkg-config --cflags libcurl`
LDFLAGS=`pkg-config --libs libcurl`

FILES=aducid soap aducidsoap utils test peig httpclient attrlist myxml
OBJS=aducid.o soap.o aducidsoap.o utils.o peig.o httpclient.o attrlist.o myxml.o

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

all: library aducidtest

aducidtest: $(OBJS)
	$(MAKE) -C ../tests


library: $(OBJS)
	$(LD) -shared -o libaducid.so.$(VERSION) -soname=libaducid.so.$(MAJORVERSION) $(OBJS)
	test -L libaducid.so.$(MAJORVERSION) || ln -s libaducid.so.$(VERSION) libaducid.so.$(MAJORVERSION)
	test -L libaducid.so || ln -s libaducid.so.$(VERSION) libaducid.so

test-dynamic-link: 
	ln -s ../test/test-dynamic-link.c
	$(CC) test-dynamic-link.c -o $@ $^ $(CFLAGS) -L. -laducid $(LDFLAGS)

clean:
	/bin/rm -f *.o *~ aducidtest libaducid.so* test-dynamic-link
	find . -type l -exec /bin/rm {} \;
	$(MAKE) -C ../tests clean
