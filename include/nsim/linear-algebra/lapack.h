
#ifndef _LinearAlgebra_LAPACK_H_
#define _LinearAlgebra_LAPACK_H_

extern "C" {

  void dgeqrf_(int*,int*,double*,int*,double*,double*,int*,int*);
  void dsyevd_(char*,char*,int*,double*,int*,double*,double*,int*,
               int*,int*,int*);
  void dspevd_(char*,char*,int*,double*,double*,double*,int*,double*,int*,
               int*,int*,int*);

  void sgeqrf_(int*,int*,float*,int*,float*,float*,int*,int*);
  void ssyevd_(char*,char*,int*,float*,int*,float*,float*,int*,
               int*,int*,int*);
  void sspevd_(char*,char*,int*,float*,float*,float*,int*,float*,int*,
               int*,int*,int*);

}

namespace mysimulator {

  template <typename T>
  struct LAPACK {

    typedef
      void (*SyEVDType)(char*,char*,int*,T*,int*,T*,T*,int*,int*,int*,int*);

    static const SyEVDType  SyEVD;

  };

}

#include <cstdlib>

namespace mysimulator {

  template <typename T>
  const typename LAPACK<T>::SyEVDType LAPACK<T>::SyEVD=NULL;

  template <>
  const typename LAPACK<double>::SyEVDType LAPACK<double>::SyEVD=dsyevd_;
  template <>
  const typename LAPACK<float>::SyEVDType LAPACK<float>::SyEVD=ssyevd_;

}

#endif

