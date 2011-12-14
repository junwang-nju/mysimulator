
#ifndef _System_Content_WithEGV_Allocate_H_
#define _System_Content_WithEGV_Allocate_H_

#include "system/content/with-egv/interface.h"
#include "system/content/with-eg/allocate.h"

namespace mysimulator {

  template <typename T, template<typename> class VecType>
  void allocate(SysContentWithEGV<T,VecType>& S, const VecType<T>& iX) {
    assert(IsValid(iX));
    release(S);
    typedef typename SysContentWithEGV<T,VecType>::ParentType   Type;
    allocate(static_cast<Type&>(S),iX);
    imprint(S.Velocity(),iX);
  }

}

#endif

