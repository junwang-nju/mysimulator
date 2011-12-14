
#ifndef _System_Content_WithEG_Allocate_H_
#define _System_Content_WithEG_Allocate_H_

#include "system/content/with-eg/interface.h"
#include "system/content/with-e/allocate.h"

namespace mysimulator {

  template <typename T, template<typename> class VecType>
  void allocate(SysContentWithEG<T,VecType>& S, const VecType<T>& iX) {
    assert(IsValid(iX));
    release(S);
    typedef typename SysContentWithEG<T,VecType>::ParentType  Type;
    allocate(static_cast<Type&>(S),iX);
    imprint(S.Gradient,iX);
  }

}

#endif

