
#ifndef _System_Content_WithV_Allocate_H_
#define _System_Content_WithV_Allocate_H_

#include "system/content/with-v/interface.h"
#include "system/content/base/allocate.h"

namespace mysimulator {

  template <typename T, template<typename> class VT, typename T1>
  void allocate(SysContentWithV<T,VT>& S, const VT<T1>& X) {
    assert(IsValid(X));
    release(S);
    typedef typename SysContentWithV<T,VT>::ParentType   Type;
    allocate(static_cast<Type&>(S),X);
    _imprint_structure(S.Velocity,X);
  }

  template <typename T, template<typename> class VT, typename T1>
  void allocate(SysContentWithV<T,VT>& S, const Object<VT<T1> >& X) {
    assert(IsValid(X));
    allocate(S,X());
  }

}

#endif

