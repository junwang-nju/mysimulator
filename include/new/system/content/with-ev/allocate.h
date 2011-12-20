
#ifndef _System_Content_WithEV_Allocate_H_
#define _System_Content_WithEV_Allocate_H_

#include "system/content/with-ev/interface.h"
#include "system/content/with-e/allocate.h"

namespace mysimulator {

  template <typename T, template<typename> class VT, typename T1>
  void allocate(SysContentWithEV<T,VT>& S, const VT<T1>& X) {
    assert(IsValid(X));
    release(S);
    typedef typename SysContentWithEV<T,VT>::ParentType    Type;
    allocate(static_cast<Type&>(S),X);
    _imprint_structure(S.Velocity,X);
  }

  template <typename T, template<typename> class VT, typename T1>
  void allocate(SysContentWithEV<T,VT>& S, const Object<VT<T1> >& X) {
    assert(IsValid(X));
    allocate(S,X());
  }

}

#endif

