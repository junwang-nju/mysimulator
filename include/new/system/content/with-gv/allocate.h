
#ifndef _System_Content_WithGV_Allocate_H_
#define _System_Content_WithGV_Allocate_H_

#include "system/content/with-gv/interface.h"
#include "system/content/with-g/allocate.h"

namespace mysimulator {

  template <typename T, template<typename> class VT, typename T1>
  void allocate(SysContentWithGV<T,VT>& S, const VT<T1>& X) {
    assert(IsValid(X));
    release(S);
    typedef typename SysContentWithGV<T,VT>::ParentType  Type;
    allocate(static_cast<Type&>(S),X);
    _imprint_structure(S.Velocity,X);
  }

}

#endif

