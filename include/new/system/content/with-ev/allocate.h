
#ifndef _System_Content_WithEV_Allocate_H_
#define _System_Content_WithEV_Allocate_H_

#include "system/content/with-ev/interface.h"
#include "system/content/with-e/allocate.h"

namespace mysimulator {

  template <typename T, template<typename> class VT>
  void allocate(SysContentWithEV<T,VT>& S, const VT<T>& iX) {
    assert(IsValid(iX));
    release(S);
    typedef typename SysContentWithEV<T,VT>::ParentType   Type;
    allocate(static_cast<Type&>(S),iX);
    imprint(S.Velocity,iX);
  }

}

#endif

