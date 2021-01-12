CLANG = clang -target ve-linux
CLFLAGS = -O3 -ffast-math -mvepacked

all: test_daxpy

test_daxpy.o: test_daxpy.c
	$(CLANG) $(CLFLAGS) -o $@ -c $<

daxpy.o: daxpy.c
	$(CLANG) $(CLFLAGS) -o $@ -c $<

test_daxpy: test_daxpy.o daxpy.o
	$(CLANG) $(CLFLAGS) -o $@ $^

run: test_daxpy
	./test_daxpy

clean:
	rm -f *.o test_daxpy
