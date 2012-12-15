
#ifndef _Array_2D_Def_H_
#define _Array_2D_Def_H_

#include "array/kernel/name.h"
#include "array/monomer/value/flag.h"

namespace mysimulator {

  template <typename T,ArrayKernelName DKernel=ArrayKernelName::Simple,
            ArrayKernelName LKernel=ArrayKernelName::Simple,
            bool _vFLAG=__array_value<T>::FLAG>
  class Array2D {

    public:

      typedef Array2D<T,DKernel,LKernel,_vFLAG>   Type;

      Array2D() = delete;
      Array2D(const Type&) = delete;
      ~Array2D() {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T1,ArrayKernelName DK1,ArrayKernelName LK1,bool vF1,
            typename T2,ArrayKernelName DK2,ArrayKernelName LK2,bool vF2>
  bool __is_same(Array2D<T1,DK1,LK1,vF1> const& A1,
                 Array2D<T2,DK2,LK2,vF2> const& A2) {
    if(A1.size()!=A2.size())  return false;
    for(unsigned int i=0;i<A1.size();++i)
      if(A1[i].size()!=A2[i].size())  return false;
    return true;
  }

}

#endif

