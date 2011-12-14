
#ifndef _System_Content_WithE_Allocate_H_
#define _System_Content_WithE_Allocate_H_

#include "system/content/with-e/interface.h"
#include "system/content/base/allocate.h"

namespace mysimulator {

  template <typename T, template<typename> class VecType>
  void allocate(SysContentWithE<T,VecType>& S, const VecType<T>& iX) {
    assert(IsValid(iX));
    typedef typename SysContentWithE<T,VecType>::ParentType Type;
    allocate(static_cast<Type&>(S),iX);
    allocate(S.Energy);
  }

}

#endif

