
#ifndef _Array_2D_Kernel_Allocate_H_
#define _Array_2D_Kernel_Allocate_H_

#include "array-2d/def.h"
#include "array/interface.h"

namespace mysimulator {

  template <typename T,ArrayKernelName DK,ArrayKernelName LK,bool vF>
  void
  __allocate_2d(Array2D<T,DK,LK,vF>& A,unsigned int n, unsigned int dim) {
    A.reset();
    A._data.allocate(n*dim);
    ((Array<Array<T,LK>>&)A).allocate(n);
    for(unsigned int i=0,w=0;i<n;w+=dim,++i) A[i].refer(A._data,w,dim);
  }

  template <typename T,ArrayKernelName DK,bool vF>
  void __allocate_2d(Array2D<T,DK,ArrayKernelName::SSE,vF>& A,
                     unsigned int n,unsigned int dim) {
    fprintf(stderr,"Not Implemented for these kernels!\n");
  }

  template <typename T,bool vF>
  void __allocate_2d(
      Array2D<T,ArrayKernelName::SSE,ArrayKernelName::SSE,vF>& A,
      unsigned int n,unsigned int dim) {
    A.reset();
    unsigned int rdim=__span16<T>(dim);
    A._data.allocate(n*rdim);
    ((Array<Array<T,ArrayKernelName::SSE>>&)A).allocate(n);
    for(unsigned int i=0,w=0;i<n;w+=rdim,++i) A[i].refer(A._data,w,dim);
  }

  template <typename T,ArrayKernelName DK,ArrayKernelName LK,bool vF,
            typename Y,ArrayKernelName YK>
  void
  __allocate_2d(Array2D<T,DK,LK,vF>& A, Array<Intrinsic<Y>,YK> const& SZ) {
    static_assert(Intrinsic<Y>::IsInteger,
                  "Only Integer permitted as size of allocation!\n");
    assert((bool)SZ);
    A.reset();
    A._data.allocate(Sum(SZ));
    ((Array<Array<T,LK>>&)A).allocate(SZ.size());
    for(unsigned int i=0,w=0;i<SZ.size();w+=SZ[i++])
      A[i].refer(A._data,w,SZ[i]);
  }

  template <typename T,ArrayKernelName DK,bool vF,typename Y,ArrayKernelName YK>
  void __allocate_2d(Array2D<T,DK,ArrayKernelName::SSE,vF>& A,
                     Array<Intrinsic<Y>,YK> const& SZ) {
    fprintf(stderr,"Not Implemented for these kernels!\n");
  }

  template <typename T,bool vF,typename Y,ArrayKernelName YK>
  void __allocate_2d(
      Array2D<T,ArrayKernelName::SSE,ArrayKernelName::SSE,vF>& A,
      Array<Intrinsic<Y>,YK> const& SZ) {
    assert((bool)SZ);
    Array<UInt> rSZ(SZ.size());
    for(unsigned int i=0;i<SZ.size();++i) {
      assert(SZ[i]>0);
      rSZ[i]=__span16<T>(SZ[i]);
    }
    A.reset();
    A._data.allocate(Sum(rSZ));
    ((Array<Array<T,ArrayKernelName::SSE>>&)A).allocate(SZ.size());
    for(unsigned int i=0,w=0;i<A.size();w+=rSZ[i++])
      A[i].refer(A._data,w,SZ[i]);
  }

}

#endif

