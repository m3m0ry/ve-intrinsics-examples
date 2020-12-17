#include <stdio.h>
#include <stdlib.h>

int ftrace_region_begin(const char *id);
int ftrace_region_end(const char *id);

#define FTRACE(N,X)  do{                        \
    ftrace_region_begin(N);                     \
    X;                                          \
    ftrace_region_end(N);                       \
  } while(0)


void daxpy(int n, double alpha, double *x, int incx,
           double *y, int incy);
void daxpy_unr(int n, double alpha, double *x, int incx,
               double *y, int incy);


int main(int argc, char *argv[])
{
  int n = 4000000;
  if (argc > 1) {
    n = atoi(argv[1]);
  }

  printf("LLVM intrinsics DAXPY on one VE core: n = %d\n", n);
  double *x = (double *)malloc(n * sizeof(double));
  double *y = (double *)malloc(n * sizeof(double));
  if (!x || !y) {
    printf("ERROR: failed to allocate memory!\n");
    exit(1);
  }

  for (int i = 0; i < n; i++) {
    x[i] = 0.1 * (double)i;
    y[i] = 1.0;
  }

  for (int i = 0; i < 100; i++)
    FTRACE("daxpy", daxpy(n, 2.0, x, 1, y, 1));

  for (int i = 0; i < 100; i++)
    FTRACE("daxpy_unr", daxpy_unr(n, 2.0, x, 1, y, 1));

  free(x);
  free(y);
  return 0;
}
