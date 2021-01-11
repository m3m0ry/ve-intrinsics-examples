Current Docker-Compiler Toolchain
  _______________________

```
bash-4.4$ make
ncc -ftrace -O3 -o test_daxpy.o -c test_daxpy.c
Invoked: ncc -ftrace -O3 -o test_daxpy.o -c test_daxpy.c
Running: gcc -E -D__NCC__ -imacros /usr/include/nognu -O3 test_daxpy.c
[gcc] Program failed..
make: *** [Makefile:12: test_daxpy.o] Error 1
```
