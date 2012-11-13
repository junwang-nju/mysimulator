
#ifndef _Array_Kernel_Simple_H_
#define _Array_Kernel_Simple_H_

#include "array/def.h"
#include "basic/memory/deleter.h"
#include <cassert>

namespace mysimulator {

  template <typename T>
  void __allocate_simple(Array<T>& A,unsigned int size) {
    assert(size>0);
    typedef typename Array<T>::monomer_type MT;
    A._pdata.reset(new MT[size],__delete_array<MT>);
    A._ndata=size;
  }

  template <typename T>
  void __copy_simple(Array<T>& A, const Array<T>& B) {
    assert((bool)A);
    assert((bool)B);
    assert(A.size()<=B.size());
    for(unsigned int i=0;i<A.size();++i)  A[i]=B[i];
  }

  template <typename T>
  void __mono_copy_simple(Array<T>& A,
                         const typename Array<T>::monomer_type& D) {
    assert((bool)A);
    for(unsigned int i=0;i<A.size();++i)  A[i]=D;
  }

  template <typename T, typename VT>
  void __value_copy_simple(Array<T>& A, const VT& D) {
    assert((bool)A);
    for(unsigned int i=0;i<A.size();++i)  A[i]=D;
  }

  template <typename T>
  void __refer_simple(Array<T>& A, Array<T> const& B,
                     unsigned int bg, unsigned int num) {
    assert( bg + num <= A.size() );
    assert( (bool) B );
    A._pdata.reset(B._pdata,bg);
    A._ndata = num;
  }

}

#include "array/expression/sum.h"

namespace mysimulator {

  template <typename T,typename EA,typename EB>
  void __assign_sum_simple(Array<T>& A, ArraySum<EA,EB> const& E) {
    assert((bool)A);
    assert((bool)E);
    assert(A.size()<=E.size());
    for(unsigned int i=0;i<A.size();++i)  A[i]=E[i];
  }

}

#endif

