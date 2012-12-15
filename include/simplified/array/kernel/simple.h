
#ifndef _Array_Kernel_Simple_H_
#define _Array_Kernel_Simple_H_

#include "array/def.h"
#include "basic/memory/access-pointer.h"
#include "basic/memory/deleter.h"
#include <cassert>

namespace mysimulator {

  template <typename T,ArrayKernelName KN,bool vF>
  void __allocate_simple(Array<T,KN,vF>& A, unsigned int size) {
    assert(size>0);
    A.reset();
    typedef typename Array<T,KN,vF>::monomer_type MT;
    A._pdata.reset(new MT[size],__delete_array<MT>);
    A._ndata=size;
  }

  template <typename T,ArrayKernelName KN,bool vF,
            typename T1,ArrayKernelName KN1,bool vF1>
  Array<T,KN,vF>& __copy_simple(Array<T,KN,vF>& A, Array<T1,KN1,vF1> const& B) {
    assert((bool)A);
    assert((bool)B);
    assert(A.size()<=B.size());
    for(unsigned int i=0;i<A.size();++i)  A[i]=B[i];
    return A;
  }

  template <typename T,ArrayKernelName KN,bool vF>
  Array<T,KN,vF>& __mono_copy_simple(
      Array<T,KN,vF>& A,
      typename Array<T,KN,vF>::monomer_type const& D) {
    assert((bool)A);
    for(unsigned int i=0;i<A.size();++i)  A[i]=D;
    return A;
  }

  template <typename T,ArrayKernelName KN,bool vF, ArrayKernelName KN1>
  void __refer_part_simple(Array<T,KN,vF>& A, Array<T,KN1,vF> const& B,
                           unsigned int bg,unsigned int num) {
    assert((bool)B);
    assert(bg+num<=B.size());
    A._pdata.reset(B._pdata,bg);
    A._ndata=num;
  }

  template <typename T,ArrayKernelName KN,bool vF,typename vT>
  Array<T,KN,vF>& __value_copy_simple(Array<T,KN,vF>& A,vT const& D) {
    assert((bool)A);
    for(unsigned int i=0;i<A.size();++i)  A[i]=D;
    return A;
  }

  template <typename E>
  typename E::value_type __sum_simple(E const& A) {
    assert((bool)A);
    typename E::value_type S=0;
    for(unsigned int i=0;i<A.size();++i)  S+=A[i];
    return S;
  }

}

#include "array/expression/sum.h"

namespace mysimulator {

  template <typename T,ArrayKernelName KN,bool vF,typename EA,typename EB>
  Array<T,KN,vF>&
  __copy_sum_simple(Array<T,KN,vF>& A,ArraySum<EA,EB> const& E) {
    assert((bool)A);
    assert((bool)E);
    assert(A.size()<=E.size());
    for(unsigned int i=0;i<A.size();++i)  A[i]=E[i];
    return A;
  }

}

#include "array/expression/substract.h"

namespace mysimulator {

  template <typename T,ArrayKernelName KN,bool vF,typename EA,typename EB>
  Array<T,KN,vF>&
  __copy_sub_simple(Array<T,KN,vF>& A,ArraySub<EA,EB> const& E) {
    assert((bool)A);
    assert((bool)E);
    assert(A.size()<=E.size());
    for(unsigned int i=0;i<A.size();++i)  A[i]=E[i];
    return A;
  }

}

#include "array/expression/multiple.h"

namespace mysimulator {

  template <typename T,ArrayKernelName KN,bool vF,typename EA,typename EB>
  Array<T,KN,vF>&
  __copy_mul_simple(Array<T,KN,vF>& A,ArrayMul<EA,EB> const& E) {
    assert((bool)A);
    assert((bool)E);
    assert(A.size()<=E.size());
    for(unsigned int i=0;i<A.size();++i)  A[i]=E[i];
    return A;
  }

}

#include "array/expression/divide.h"

namespace mysimulator {

  template <typename T,ArrayKernelName KN,bool vF,typename EA,typename EB>
  Array<T,KN,vF>&
  __copy_div_simple(Array<T,KN,vF>& A,ArrayDiv<EA,EB> const& E) {
    assert((bool)A);
    assert((bool)E);
    assert(A.size()<=E.size());
    for(unsigned int i=0;i<A.size();++i)  A[i]=E[i];
    return A;
  }

  template <typename EA,typename EB>
  typename __dual_selector<typename EA::value_type,typename EB::value_type,
                           __mul>::Type
  __dot_simple(EA const& A, EB const& B) {
    typename __dual_selector<typename EA::value_type,typename EB::value_type,
                             __mul>::Type S=0;
    unsigned int n=(A.size()<B.size()?A.size():B.size());
    for(unsigned int i=0;i<n;++i)   S+=A[i]*B[i];
    return S;
  }

}

#include "basic/util/square-root.h"

namespace mysimulator {

  template <typename T>
  Array<T,ArrayKernelName::Simple,true>&
  __square_root_simple(Array<T,ArrayKernelName::Simple,true>& A) {
    assert((bool)A);
    for(unsigned int i=0;i<A.size();++i)  A[i]=__square_root(A[i]);
    return A;
  }

  template <typename T,ArrayKernelName KN>
  Array<T,KN,true>&
  __inv_square_root_simple(Array<T,KN,true>& A) {
    assert((bool)A);
    for(unsigned int i=0;i<A.size();++i)  A[i]=1./__square_root(A[i]);
    return A;
  }

}

#endif

