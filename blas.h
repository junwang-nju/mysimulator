
#ifndef _BLAS_H_
#define _BLAS_H_

extern "C" {

  void dcopy_(long* N,double* X,long* dX,double* Y,long* dY);

  void scopy_(long* N,float* X,long* dX,float* Y,long* dY);

  void dswap_(long*,double*,long*,double*,long*);

  void sswap_(long*,float*,long*,float*,long*);

  double ddot_(long* N,double* X,long* dX,double* Y,long* dY);

  float sdot_(long*,float*,long*,float*,long*);

  double dnrm2_(long* N,double* X,long* dX);

  float snrm2_(long*,float*,long*);

  double dasum_(long* N,double* X,long* dX);

  float sasum_(long* N,float* X,long* dX);

  void dscal_(long*,double*,double*,long*);

  void sscal_(long*,float*,float*,long*);

  void daxpy_(long* N,double* a,double* X,long* dX,double* Y,long* dY);

  void saxpy_(long* N,float* a,float* X,long* dX,float* Y,long* dY);

  void dtbmv_(char* UPLO,char* TRANS,char* DIAG,long* N,long* K,double* A,
              long* LDA,double* X,long* dX);

  void stbmv_(char* UPLO,char* TRANS,char* DIAG,long* N,long* K,float* A,
              long* LDA,float* X,long* dX);

  void dsbmv_(char* UPLO,long* N,long* K,double* a,double* A,long* LDA,
              double* X,long* dX,double* b,double* Y,long* dY);

  void ssbmv_(char* UPLO,long* N,long* K,float* a,float* A,long* LDA,
              float* X,long* dX,float* b,float* Y,long* dY);

  void dgemv_(char* TRANS,long* M,long* N,double* a,double* A,long* LDA,
              double* X,long* dX,double* b,double* Y,long* dY);

  void sgemv_(char* TRANS,long* M,long* N,float* a,float* A,long* LDA,
              float* X,long* dX,float* b,float* Y,long* dY);

}

#endif

