
#ifndef _System_Content_WithG_Copy_H_
#define _System_Content_WithG_Copy_H_

#include "system/content/with-g/interface.h"
#include "system/content/base/copy.h"
#include "system/content/data/g/copy.h"

namespace mysimulator {

  template <typename T, template<typename> class VT>
  void copy(SysContentWithG<T,VT>& S, const SysContentWithG<T,VT>& cS) {
    assert(IsValid(S)&&IsValid(cS));
    typedef typename SysContentWithG<T,VT>::ParentType  Type;
    copy(static_cast<Type&>(S),static_cast<const Type&>(cS));
    copy(S.EGData,cS.EGData);
  }

}

#endif

