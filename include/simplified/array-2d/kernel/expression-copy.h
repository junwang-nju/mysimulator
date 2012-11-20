
#ifndef _Array_2D_Kernel_Expression_Copy_H_
#define _Array_2D_Kernel_Expression_Copy_H_

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

