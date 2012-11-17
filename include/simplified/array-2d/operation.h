
#ifndef _Array_2D_Operation_H_
#define _Array_2D_Operation_H_

#include "array-2d/def.h"
#include <cstdio>
#include <cassert>

namespace mysimulator {

  template <typename T,ArrayKernelName DK,ArrayKernelName LK,bool vF>
  void
  __allocate_2d(Array2D<T,DK,LK,vF>& A,unsigned int n, unsigned int dim) {
    fprintf(stderr,"Not Implemented for these kernels!\n");
  }

  template <typename T,bool vF>
  void __allocate_2d(
      Array2D<T,ArrayKernelName::Simple,ArrayKernelName::Simple,vF>& A,
      unsigned int n,unsigned int dim) {
    A.reset();
    A._data.allocate(n*dim);
    ((Array<Array<T,ArrayKernelName::Simple>>&)A).allocate(n);
    for(unsigned int i=0,w=0;i<n;w+=dim,++i) A[i].refer(A._data,w,dim);
  }

  template <typename T,ArrayKernelName DK,ArrayKernelName LK,bool vF,
            typename Y,ArrayKernelName YK>
  void
  __allocate_2d(Array2D<T,DK,LK>& A, Array<Intrinsic<Y>,YK> const& SZ) {
    fprintf(stderr,"Not Implemented for these kernels!\n");
  }

  template <typename T,bool vF,typename Y,ArrayKernelName YK>
  void __allocate_2d(
      Array2D<T,ArrayKernelName::Simple,ArrayKernelName::Simple,vF>& A,
      Array<Intrinsic<Y>,YK> const& SZ) {
    static_assert(Intrinsic<Y>::IsInteger,
                  "Only Integer permitted as size of allocation!\n");
    assert((bool)SZ);
    A.reset();
    A._data.allocate(SZ.Sum());
    ((Array<Array<T,ArrayKernelName::Simple>>&)A).allocate(SZ.size());
    for(unsigned int i=0,w=0;i<SZ.size();w+=SZ[i++])
      A[i].refer(A._data,w,SZ[i]);
  }

}

#endif

