
#ifndef _System_Content_WithEG_Allocate_H_
#define _System_Content_WithEG_Allocate_H_

#include "system/content/with-eg/interface.h"
#include "system/content/base/allocate.h"
#include "system/content/data/eg/allocate.h"

namespace mysimulator {

  template <typename T, template<typename> class VT, typename T1>
  void allocate(SysContentWithEG<T,VT>& S, const VT<T1>& X) {
    assert(IsValid(X));
    release(S);
    typedef typename SysContentWithEG<T,VT>::ParentType  Type;
    allocate(static_cast<Type&>(S),X);
    allocate(S.EGData,X);
  }

  template <typename T, template<typename> class VT, typename T1>
  void allocate(SysContentWithEG<T,VT>& S, const Object<VT<T1> >& X) {
    assert(IsValid(X));
    allocate(S,X());
  }

}

#endif

