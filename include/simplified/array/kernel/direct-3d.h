
#ifndef _Array_Kernel_Direct3D_H_
#define _Array_Kernel_Direct3D_H_

#include "array/def.h"
#include "array/expression/sum.h"
#include <cassert>

namespace mysimulator {

  template <typename T,ArrayKernelName K,bool vF,typename EA,typename EB>
  Array<T,K,vF>&
  __copy_sum_direct3d(Array<T,K,vF>& A,ArraySum<EA,EB> const& E) {
    assert((bool)A);
    assert((bool)E);
    assert(A.size()<=E.size());
    A[0]=E[0];
    A[1]=E[1];
    A[2]=E[2];
    return A;
  }

}

#include "array/expression/substract.h"

namespace mysimulator {

  template <typename T,ArrayKernelName K,bool vF,typename EA,typename EB>
  Array<T,K,vF>&
  __copy_sub_direct3d(Array<T,K,vF>& A,ArraySub<EA,EB> const& E) {
    assert((bool)A);
    assert((bool)E);
    assert(A.size()<=E.size());
    A[0]=E[0];
    A[1]=E[1];
    A[2]=E[2];
    return A;
  }

}

#include "array/expression/multiple.h"

namespace mysimulator {

  template <typename T,ArrayKernelName K,bool vF,typename EA,typename EB>
  Array<T,K,vF>&
  __copy_mul_direct3d(Array<T,K,vF>& A,ArrayMul<EA,EB> const& E) {
    assert((bool)A);
    assert((bool)E);
    assert(A.size()<=E.size());
    A[0]=E[0];
    A[1]=E[1];
    A[2]=E[2];
    return A;
  }

}

#include "array/expression/divide.h"

namespace mysimulator {

  template <typename T,ArrayKernelName K,bool vF,typename EA,typename EB>
  Array<T,K,vF>&
  __copy_div_direct3d(Array<T,K,vF>& A,ArrayDiv<EA,EB> const& E) {
    assert((bool)A);
    assert((bool)E);
    assert(A.size()<=E.size());
    A[0]=E[0];
    A[1]=E[1];
    A[2]=E[2];
    return A;
  }

}

#endif

