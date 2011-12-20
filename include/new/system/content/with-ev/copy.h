
#ifndef _System_Content_WithEV_Copy_H_
#define _System_Content_WithEV_Copy_H_

#include "system/content/with-ev/interface.h"
#include "system/content/with-e/copy.h"

namespace mysimulator {

  template <typename T, template<typename> class VT>
  void copy(SysContentWithEV<T,VT>& S, const SysContentWithEV<T,VT>& cS) {
    assert(IsValid(S)&&IsValid(cS));
    typedef typename SysContentWithEV<T,VT>::ParentType   Type;
    copy(static_cast<Type&>(S),static_cast<const Type&>(cS));
    copy(S.Velocity,cS.Velocity);
  }

}

#endif

