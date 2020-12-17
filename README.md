## Prerequisite

Install LLVM-VE-RV-1.8.0 from
https://sx-aurora.com/repos/llvm/x86_64/llvm-ve-rv-1.8.0-1.8.0-1.x86_64.rpm


Set environment for LLVM-VE-RV
```
. llvmvervvars.sh
```

## Build

```
make
```

## Run

Run the test program:
```
./test_daxpy [<array_size>]
```

Print ftrace performance profile:
```
make ftrace
```

## Example

```
[focht@aurora0 Intrinsics]$ make 
/opt/nec/ve/bin/ncc -ftrace -O3 -o test_daxpy.o -c test_daxpy.c
ncc: vec( 101): test_daxpy.c, line 35: Vectorized loop.
ncc: vec( 103): test_daxpy.c, line 40: Unvectorized loop.
ncc: vec( 103): test_daxpy.c, line 43: Unvectorized loop.
clang -target ve-linux -O3 -ffast-math -mvepacked -o daxpy.o -c daxpy.c
/opt/nec/ve/bin/ncc -ftrace -O3 -o test_daxpy test_daxpy.o daxpy.o
[focht@aurora0 Intrinsics]$ ./test_daxpy 
n = 4000000
[focht@aurora0 Intrinsics]$ make ftrace
/opt/nec/ve/bin/ftrace -f ftrace.out
*----------------------*
  FTRACE ANALYSIS LIST
*----------------------*

Execution Date : Thu Dec 17 03:36:23 2020 CET
Total CPU Time : 0:00'00"055 (0.055 sec.)


FREQUENCY  EXCLUSIVE       AVER.TIME     MOPS   MFLOPS  V.OP  AVER.    VECTOR L1CACHE CPU PORT VLD LLC PROC.NAME  
           TIME[sec](  % )    [msec]                    RATIO V.LEN      TIME    MISS     CONF HIT E.%            

        1     0.055(100.0)    55.126  73407.3  29097.1  99.44 256.0     0.055   0.000    0.000    0.00 main
------------------------------------------------------------------------------------------------------------------
        1     0.055(100.0)    55.126  73407.3  29097.1  99.44 256.0     0.055   0.000    0.000    0.00 total

      100     0.028( 51.4)     0.283  71239.1  28249.8  99.14 256.0     0.028   0.000    0.000    0.00 daxpy
      100     0.026( 48.1)     0.265  75683.3  30198.3  99.75 256.0     0.026   0.000    0.000    0.00 daxpy_unr
------------------------------------------------------------------------------------------------------------------
```
