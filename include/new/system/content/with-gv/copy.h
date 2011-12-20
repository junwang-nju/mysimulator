
#ifndef _System_Content_WithGV_Copy_H_
#define _System_Content_WithGV_Copy_H_

#include "system/content/with-gv/interface.h"
#include "system/content/with-g/copy.h"

namespace mysimulator {

  template <typename T, template<typename> class VT>
  void copy(SysContentWithGV<T,VT>& S, const SysContentWithGV<T,VT>& cS) {
    assert(IsValid(S)&&IsValid(cS));
    typedef typename SysContentWithGV<T,VT>::ParentType   Type;
    copy(static_cast<Type&>(S),static_cast<const Type&>(cS));
    copy(S.Velocity,cS.Velocity);
  }

}

#endif

