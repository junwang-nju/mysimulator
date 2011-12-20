
#ifndef _System_Content_WithE_Allocate_H_
#define _System_Content_WithE_Allocate_H_

#include "system/content/with-e/interface.h"
#include "system/content/base/allocate.h"
#include "system/content/data/e/allocate.h"

namespace mysimulator {

  template <typename T, template<typename> class VT, typename T1>
  void allocate(SysContentWithE<T,VT>& S, const VT<T1>& X) {
    assert(IsValid(X));
    release(S);
    typedef typename SysContentWithE<T,VT>::ParentType Type;
    allocate(static_cast<Type&>(S),X);
    allocate(S.EGData);
  }

  template <typename T, template<typename> class VT, typename T1>
  void allocate(SysContentWithE<T,VT>& S, const Object<VT<T1> >& X) {
    assert(IsValid(X));
    allocate(S,X());
  }

}

#endif

