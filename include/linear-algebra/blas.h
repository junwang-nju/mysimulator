
#ifndef _LinearAlgebra_BLAS_H_
#define _LinearAlgebra_BLAS_H_

extern "C" {

  void dcopy_(long*,double*,long*,double*,long*);
  void dswap_(long*,double*,long*,double*,long*);
  double ddot_(long*,double*,long*,double*,long*);
  double dnrm2_(long*,double*,long*);
  double dasum_(long*,double*,long*);
  void dscal_(long*,double*,double*,long*);
  void daxpy_(long*,double*,double*,long*,double*,long*);
  void dtbmv_(char*,char*,char*,long*,long*,double*,long*,double*,long*);
  void dsbmv_(char*,long*,long*,double*,double*,long*,double*,long*,
              double*,double*,long*);
  void dgemv_(char*,long*,long*,double*,double*,long*,double*,long*,
              double*,double*,long*);

  void scopy_(long*,float*,long*,float*,long*);
  void sswap_(long*,float*,long*,float*,long*);
  float sdot_(long*,float*,long*,float*,long*);
  float snrm2_(long*,float*,long*);
  float sasum_(long*,float*,long*);
  void sscal_(long*,float*,float*,long*);
  void saxpy_(long*,float*,float*,long*,float*,long*);
  void stbmv_(char*,char*,char*,long*,long*,float*,long*,float*,long*);
  void ssbmv_(char*,long*,long*,float*,float*,long*,float*,long*,
              float*,float*,long*);
  void sgemv_(char*,long*,long*,float*,float*,long*,float*,long*,
              float*,float*,long*);

}

#endif

