LDFLAGS=`pkg-config --libs libcurl`

aducidtest:
	gcc test.c -o $@ $^ $(CFLAGS) $(LDFLAGS) -L ../src -laducid

clean:
	/bin/rm -f aducidtest
