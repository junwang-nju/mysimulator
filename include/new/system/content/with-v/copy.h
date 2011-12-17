
#ifndef _System_Content_WithV_Copy_H_
#define _System_Content_WithV_Copy_H_

#include "system/content/with-v/interface.h"
#include "system/content/base/copy.h"

namespace mysimulator {

  template <typename T, template <typename> class VT>
  void copy(SysContentWithV<T,VT>& S, const SysContentWithV<T,VT>& rS) {
    assert(IsValid(S)&&IsValid(rS));
    typedef typename SysContentWithV<T,VT>::ParentType  Type;
    copy(static_cast<Type&>(S),static_cast<const Type&>(rS));
    copy(S.Velocity,rS.Velocity);
  }

}

#endif

