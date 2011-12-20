
#ifndef _System_Content_WithV_Copy_H_
#define _System_Content_WithV_Copy_H_

#include "system/content/with-v/interface.h"
#include "system/content/base/copy.h"

namespace mysimulator {

  template <typename T, template<typename> class VT>
  void copy(SysContentWithV<T,VT>& S, const SysContentWithV<T,VT>& cS) {
    assert(IsValid(S)&&IsValid(cS));
    typedef typename SysContentWithV<T,VT>::ParentType  Type;
    copy(static_cast<Type&>(S),static_cast<const Type&>(cS));
    copy(S.Velocity,cS.Velocity);
  }

}

#endif

