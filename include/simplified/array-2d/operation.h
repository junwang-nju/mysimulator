
#ifndef _Array_2D_Operation_H_
#define _Array_2D_Operation_H_

#include "array-2d/def.h"
#include <cstdio>
#include <cassert>

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
    fprintf(stderr,"To Be Implemented!\n");
  }

  template <typename T,ArrayKernelName DK,ArrayKernelName LK,bool vF,
            typename Y,ArrayKernelName YK>
  void
  __allocate_2d(Array2D<T,DK,LK,vF>& A, Array<Intrinsic<Y>,YK> const& SZ) {
    static_assert(Intrinsic<Y>::IsInteger,
                  "Only Integer permitted as size of allocation!\n");
    assert((bool)SZ);
    A.reset();
    A._data.allocate(SZ.Sum());
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
    fprintf(stderr,"To Be Implemented!\n");
  }

}

#include "array-2d/expression/size-check.h"
#include "array-2d/expression/sum.h"

namespace mysimulator {

  template <typename T,ArrayKernelName DK,ArrayKernelName LK,
            typename EA,typename EB>
  Array2D<Intrinsic<T>,DK,LK,true>&
  __copy_sum_match_2d(
      Array2D<Intrinsic<T>,DK,LK,true>& A, Array2DSum<EA,EB> const& E) {
    assert((bool)A);
    assert((bool)E);
    assert(__is_expression_size_same(A,E));
    A.Data()=E.Data();
    return A;
  }

  template <typename T,ArrayKernelName DK,ArrayKernelName LK,
            typename EA,typename EB>
  Array2D<Intrinsic<T>,DK,LK,true>&
  __copy_sum_mixed_2d(
      Array2D<Intrinsic<T>,DK,LK,true>& A, Array2DSum<EA,EB> const& E) {
    assert((bool)A);
    assert((bool)E);
    assert(__is_expression_size_same(A,E));
    for(unsigned int i=0;i<A.size();++i)  A[i]=E[i];
    return A;
  }

}

#include "array-2d/expression/substract.h"

namespace mysimulator {

  template <typename T,ArrayKernelName DK,ArrayKernelName LK,
            typename EA,typename EB>
  Array2D<Intrinsic<T>,DK,LK,true>&
  __copy_sub_match_2d(
      Array2D<Intrinsic<T>,DK,LK,true>& A, Array2DSub<EA,EB> const& E) {
    assert((bool)A);
    assert((bool)E);
    assert(__is_expression_size_same(A,E));
    A.Data()=E.Data();
    return A;
  }
  template <typename T,ArrayKernelName DK,ArrayKernelName LK,
            typename EA,typename EB>
  Array2D<Intrinsic<T>,DK,LK,true>&
  __copy_sub_mixed_2d(
      Array2D<Intrinsic<T>,DK,LK,true>& A, Array2DSub<EA,EB> const& E) {
    assert((bool)A);
    assert((bool)E);
    assert(__is_expression_size_same(A,E));
    for(unsigned int i=0;i<A.size();++i)  A[i]=E[i];
    return A;
  }

}

#include "array-2d/expression/multiple.h"

namespace mysimulator {

  template <typename T,ArrayKernelName DK,ArrayKernelName LK,
            typename EA,typename EB>
  Array2D<Intrinsic<T>,DK,LK,true>&
  __copy_mul_match_2d(
      Array2D<Intrinsic<T>,DK,LK,true>& A, Array2DMul<EA,EB> const& E) {
    assert((bool)A);
    assert((bool)E);
    assert(__is_expression_size_same(A,E));
    A.Data()=E.Data();
    return A;
  }
  template <typename T,ArrayKernelName DK,ArrayKernelName LK,
            typename EA,typename EB>
  Array2D<Intrinsic<T>,DK,LK,true>&
  __copy_mul_mixed_2d(
      Array2D<Intrinsic<T>,DK,LK,true>& A, Array2DMul<EA,EB> const& E) {
    assert((bool)A);
    assert((bool)E);
    assert(__is_expression_size_same(A,E));
    for(unsigned int i=0;i<A.size();++i)  A[i]=E[i];
    return A;
  }

}

#include "array-2d/expression/divide.h"

namespace mysimulator {

  template <typename T,ArrayKernelName DK,ArrayKernelName LK,
            typename EA,typename EB>
  Array2D<Intrinsic<T>,DK,LK,true>&
  __copy_div_match_2d(
      Array2D<Intrinsic<T>,DK,LK,true>& A, Array2DDiv<EA,EB> const& E) {
    assert((bool)A);
    assert((bool)E);
    assert(__is_expression_size_same(A,E));
    A.Data()=E.Data();
    return A;
  }
  template <typename T,ArrayKernelName DK,ArrayKernelName LK,
            typename EA,typename EB>
  Array2D<Intrinsic<T>,DK,LK,true>&
  __copy_div_mixed_2d(
      Array2D<Intrinsic<T>,DK,LK,true>& A, Array2DDiv<EA,EB> const& E) {
    assert((bool)A);
    assert((bool)E);
    assert(__is_expression_size_same(A,E));
    for(unsigned int i=0;i<A.size();++i)  A[i]=E[i];
    return A;
  }

}

#endif

