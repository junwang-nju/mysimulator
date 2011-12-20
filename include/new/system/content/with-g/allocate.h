
#ifndef _System_Content_WithG_Allocate_H_
#define _System_Content_WithG_Allocate_H_

#include "system/content/with-g/interface.h"
#include "system/content/base/allocate.h"
#include "system/content/data/g/allocate.h"

namespace mysimulator {

  template <typename T, template<typename> class VT, typename T1>
  void allocate(SysContentWithG<T,VT>& S, const VT<T1>& X) {
    assert(IsValid(X));
    release(S);
    typedef typename SysContentWithG<T,VT>::ParentType   Type;
    allocate(static_cast<Type&>(S),X);
    allocate(S.EGData,X);
  }

}

#endif

