CC= gcc
CFLAGS = -shared -fPIC -o
SORUCES = *.c

all:
	$(CC) $(CFLAGS) libcommon.so $(SORUCES)
install:
	cp libcommon.so /usr/lib
	mkdir -p /usr/local/include/common
	cp *.h /usr/local/include/common
clean:
	-rm *.o *.a *.so
