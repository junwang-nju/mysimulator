
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

namespace mysimulator {

  template <typename T>
  struct BLAS {
    typedef void (*CopyType)(long*,T*,long*,T*,long*);
    typedef void (*SwapType)(long*,T*,long*,T*,long*);
    typedef T (*DotType)(long*,T*,long*,T*,long*);
    static const CopyType Copy;
    static const SwapType Swap;
    static const DotType  Dot;
  };

  template <typename T>
  const typename BLAS<T>::CopyType BLAS<T>::Copy=NULL;
  template <> const typename BLAS<double>::CopyType BLAS<double>::Copy=dcopy_;
  template <> const typename BLAS<float>::CopyType BLAS<float>::Copy=scopy_;

  template <typename T>
  const typename BLAS<T>::SwapType BLAS<T>::Swap=NULL;
  template <> const typename BLAS<double>::SwapType BLAS<double>::Swap=dswap_;
  template <> const typename BLAS<float>::SwapType BLAS<float>::Swap=sswap_;

  template <typename T>
  const typename BLAS<T>::DotType BLAS<T>::Dot=NULL;
  template <> const typename BLAS<double>::DotType BLAS<double>::Dot=ddot_;
  template <> const typename BLAS<float>::DotType BLAS<float>::Dot=sdot_;

}

#endif

