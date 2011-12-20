
#ifndef _System_Content_WithE_Copy_H_
#define _System_Content_WithE_Copy_H_

#include "system/content/with-e/interface.h"
#include "system/content/base/copy.h"
#include "system/content/data/e/copy.h"

namespace mysimulator {

  template <typename T, template<typename> class VT>
  void copy(SysContentWithE<T,VT>& S, const SysContentWithE<T,VT>& cS) {
    assert(IsValid(S)&&IsValid(cS));
    typedef typename SysContentWithE<T,VT>::ParentType Type;
    copy(static_cast<Type&>(S),static_cast<const Type&>(cS));
    copy(S.EGData,cS.EGData);
  }

}

#endif

