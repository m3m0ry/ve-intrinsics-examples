NCC = /opt/nec/ve/bin/ncc
NCCFLAGS = -O3
FTRACE = /opt/nec/ve/bin/ftrace

CLANG = clang -target ve-linux
CLFLAGS = -O3 -ffast-math -mvepacked


all: test_daxpy

test_daxpy.o: test_daxpy.c
	$(NCC) -ftrace $(NCCFLAGS) -o $@ -c $<

daxpy.o: daxpy.c
	$(CLANG) $(CLFLAGS) -o $@ -c $<

test_daxpy: test_daxpy.o daxpy.o
	$(NCC) -ftrace $(NCCFLAGS) -o $@ $^

run: test_daxpy
	./test_daxpy; $(FTRACE) -f ftrace.out

ftrace:
	$(FTRACE) -f ftrace.out

clean:
	rm -f *.o test_daxpy ftrace.out
