
#ifndef _System_Content_WithG_Allocate_H_
#define _System_Content_WithG_Allocate_H_

#include "system/content/with-g/interface.h"
#include "system/content/base/allocate.h"

namespace mysimulator {

  template <typename T, template<typename> class VecType>
  void allocate(SysContentWithG<T,VecType>& S, const VecType<T>& iX) {
    assert(IsValid(iX));
    release(S);
    typedef typename SysContentBase<T,VecType>::ParentType  Type;
    allocate(static_cast<Type&>(S),iX);
    imprint(S.Gradient(),iX);
  }

}

#endif

