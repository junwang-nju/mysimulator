
#ifndef _System_Content_WithEGV_Copy_H_
#define _System_Content_WithEGV_Copy_H_

#include "system/content/with-egv/interface.h"
#include "system/content/with-eg/copy.h"

namespace mysimulator {

  template <typename T, template<typename> class VT>
  void copy(SysContentWithEGV<T,VT>& S, const SysContentWithEGV<T,VT>& cS) {
    assert(IsValid(S)&&IsValid(cS));
    typedef typename SysContentWithEGV<T,VT>::ParentType  Type;
    copy(static_cast<Type&>(S),static_cast<const Type&>(cS));
    copy(S.Velocity,cS.Velocity);
  }

}

#endif

