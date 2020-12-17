//
// daxpy - compute y := alpha * x + y
//
//
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <velintrin.h>

#define VLEN (256)

void daxpy(int n, double alpha, double *x, int incx,
           double *y, int incy)
{

  const double *xp = (const double *)x;
  double *yp = y;
  uint64_t incx_b = sizeof(double) * incx;
  uint64_t incy_b = sizeof(double) * incy;

  for (size_t i = 0; i < n; i += VLEN) {
    const int vl = (n-i < VLEN ? n-i : VLEN);
    __vr xv = _vel_vld_vssl(incx_b, xp+i, vl);
    __vr yv = _vel_vld_vssl(incy_b, yp+i, vl);
    __vr yr = _vel_vfmadd_vvsvl(yv, alpha, xv, vl);
    _vel_vst_vssl(yr, incy_b, yp+i, vl);
  }
}

//
// unrolled version of daxpy
//
void daxpy_unr(int n, double alpha, double *x, int incx,
               double *y, int incy)
{

  const double *xp = (const double *)x;
  double *yp = y;
  uint64_t incx_b = sizeof(double) * incx;
  uint64_t incy_b = sizeof(double) * incy;

  const size_t vlen1 = 1 * VLEN;
  const size_t vlen2 = 2 * VLEN;
  const size_t vlen3 = 3 * VLEN;

  size_t i = 0;
  
  if (n >= 4*VLEN) {
    const int vl = VLEN;
    for (; i + 4*VLEN <= n; i += 4*VLEN) {
      __vr xv1 = _vel_vld_vssl(incx_b, xp+i      , vl);
      __vr xv2 = _vel_vld_vssl(incx_b, xp+i+vlen1, vl);
      __vr xv3 = _vel_vld_vssl(incx_b, xp+i+vlen2, vl);
      __vr xv4 = _vel_vld_vssl(incx_b, xp+i+vlen3, vl);
      __vr yv1 = _vel_vld_vssl(incy_b, yp+i      , vl);
      __vr yv2 = _vel_vld_vssl(incy_b, yp+i+vlen1, vl);
      __vr yv3 = _vel_vld_vssl(incy_b, yp+i+vlen2, vl);
      __vr yv4 = _vel_vld_vssl(incy_b, yp+i+vlen3, vl);
      __vr yr1 = _vel_vfmadd_vvsvl(yv1, alpha, xv1, vl);
      __vr yr2 = _vel_vfmadd_vvsvl(yv2, alpha, xv2, vl);
      __vr yr3 = _vel_vfmadd_vvsvl(yv3, alpha, xv3, vl);
      __vr yr4 = _vel_vfmadd_vvsvl(yv4, alpha, xv4, vl);
      _vel_vst_vssl(yr1, incy_b, yp+i      , vl);
      _vel_vst_vssl(yr2, incy_b, yp+i+vlen1, vl);
      _vel_vst_vssl(yr3, incy_b, yp+i+vlen2, vl);
      _vel_vst_vssl(yr4, incy_b, yp+i+vlen3, vl);
    }
  }
  if (n - i >= 2*VLEN) {
    const int vl = VLEN;
    for (; i + 2*VLEN <= n; i += 2*VLEN) {
      __vr xv1 = _vel_vld_vssl(incx_b, xp+i      , vl);
      __vr xv2 = _vel_vld_vssl(incx_b, xp+i+vlen1, vl);
      __vr yv1 = _vel_vld_vssl(incy_b, yp+i      , vl);
      __vr yv2 = _vel_vld_vssl(incy_b, yp+i+vlen1, vl);
      __vr yr1 = _vel_vfmadd_vvsvl(yv1, alpha, xv1, vl);
      __vr yr2 = _vel_vfmadd_vvsvl(yv2, alpha, xv2, vl);
      _vel_vst_vssl(yr1, incy_b, yp+i      , vl);
      _vel_vst_vssl(yr2, incy_b, yp+i+vlen1, vl);
    }
  }
  if (n - i > 0) {
    for (; i < n; i += VLEN) {
      const int vl = (n-i < VLEN ? n-i : VLEN);
      __vr xv = _vel_vld_vssl(incx_b, xp+i, vl);
      __vr yv = _vel_vld_vssl(incy_b, yp+i, vl);
      __vr yr = _vel_vfmadd_vvsvl(yv, alpha, xv, vl);
      _vel_vst_vssl(yr, incy_b, yp+i, vl);
    }
  }
}
