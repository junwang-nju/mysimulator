
#ifndef _System_Content_WithV_Allocate_H_
#define _System_Content_WithV_Allocate_H_

#include "system/content/with-v/interface.h"
#include "system/content/base/allocate.h"

namespace mysimulator {

  template <typename T, template<typename> class VT>
  void allocate(SysContentWithV<T,VT>& S, const VT<T>& iX) {
    assert(IsValid(iX));
    release(S);
    typedef typename SysContentWithV<T,VT>::ParentType  Type;
    allocate(static_cast<Type&>(S),iX);
    imprint(S.Velocity,iX);
  }

}

#endif

