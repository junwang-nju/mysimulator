
#ifndef _System_Content_WithE_Copy_H_
#define _System_Content_WithE_Copy_H_

#include "system/content/with-e/interface.h"
#include "system/content/base/copy.h"

namespace mysimulator {

  template <typename T, template <typename> class VT>
  void copy(SysContentWithE<T,VT>& S, const SysContentWithE<T,VT>& rS) {
    assert(IsValid(S)&&IsValid(rS));
    typedef typename SysContentWithE<T,VT>::ParentType Type;
    copy(static_cast<Type&>(S),static_cast<const Type&>(rS));
    copy(S.Energy,rS.Energy);
  }

}

#endif

