
#ifndef _System_Content_Base_Allocate_H_
#define _System_Content_Base_Allocate_H_

#include "system/content/base/interface.h"
#include "object/allocate.h"

namespace mysimulator {

  template <typename T, template<typename> class VT, typename T1>
  void allocate(SysContentBase<T,VT>& S, const VT<T1>& X) {
    assert(IsValid(X));
    release(S);
    _imprint_structure(S.X,X);
  }

  template <typename T, template<typename> class VT, typename T1,
            template<typename,template<typename>class> class SysContentType>
  void allocate(SysContentType<T,VT>& S, const Object<VT<T1> >& X) {
    assert(IsValid(X));
    allocate(S,X());
  }

}

#endif

