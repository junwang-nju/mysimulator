
#ifndef _System_Content_WithEGV_Copy_H_
#define _System_Content_WithEGV_Copy_H_

#include "system/content/with-egv/interface.h"
#include "system/content/with-eg/copy.h"

namespace mysimulator {

  template <typename T, template <typename> class VT>
  void copy(SysContentWithEGV<T,VT>& S, const SysContentWithEGV<T,VT>& rS) {
    assert(IsValid(S)&&IsValid(rS));
    typedef typename SysContentWithEGV<T,VT>::ParentType  Type;
    copy(static_cast<Type&>(S),static_cast<const Type&>(rS));
    copy(S.Velocity,rS.Velocity);
  }

}

#endif

