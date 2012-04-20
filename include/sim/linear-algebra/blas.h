
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
    typedef T (*NormType)(long*,T*,long*);
    typedef T (*ASumType)(long*,T*,long*);
    typedef void (*ScaleType)(long*,T*,T*,long*);
    typedef void (*TbMvType)(char*,char*,char*,long*,long*,T*,long*,T*,long*);
    typedef void (*ShiftType)(long*,T*,T*,long*,T*,long*);
    typedef void (*SbMvType)(char*,long*,long*,T*,T*,long*,T*,long*,T*,T*,
                             long*);

    static const CopyType   Copy;
    static const SwapType   Swap;
    static const DotType    Dot;
    static const NormType   Norm;
    static const ASumType   ASum;
    static const ScaleType  Scale;
    static const TbMvType   TbMv;
    static const ShiftType  Shift;
    static const SbMvType   SbMv;

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

  template <typename T>
  const typename BLAS<T>::NormType BLAS<T>::Norm=NULL;
  template <> const typename BLAS<double>::NormType BLAS<double>::Norm=dnrm2_;
  template <> const typename BLAS<float>::NormType BLAS<float>::Norm=snrm2_;

  template <typename T>
  const typename BLAS<T>::ASumType BLAS<T>::ASum=NULL;
  template <> const typename BLAS<double>::ASumType BLAS<double>::ASum=dasum_;
  template <> const typename BLAS<float>::ASumType BLAS<float>::ASum=sasum_;

  template <typename T>
  const typename BLAS<T>::ScaleType BLAS<T>::Scale=NULL;
  template <> const typename BLAS<double>::ScaleType BLAS<double>::Scale=dscal_;
  template <> const typename BLAS<float>::ScaleType BLAS<float>::Scale=sscal_;

  template <typename T>
  const typename BLAS<T>::TbMvType BLAS<T>::TbMv=NULL;
  template <> const typename BLAS<double>::TbMvType BLAS<double>::TbMv=dtbmv_;
  template <> const typename BLAS<float>::TbMvType BLAS<float>::TbMv=stbmv_;

  template <typename T>
  const typename BLAS<T>::ShiftType BLAS<T>::Shift=NULL;
  template <> const typename BLAS<double>::ShiftType BLAS<double>::Shift=daxpy_;
  template <> const typename BLAS<float>::ShiftType BLAS<float>::Shift=saxpy_;

  template <typename T>
  const typename BLAS<T>::SbMvType BLAS<T>::SbMv=NULL;
  template <> const typename BLAS<double>::SbMvType BLAS<double>::SbMv=dsbmv_;
  template <> const typename BLAS<float>::SbMvType BLAS<float>::SbMv=ssbmv_;

}

#endif

