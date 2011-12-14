
#ifndef _System_Content_WithMEGV_Allocate_H_
#define _System_Content_WithMEGV_Allocate_H_

#include "system/content/with-megv/interface.h"
#include "system/content/with-egv/allocate.h"

namespace mysimulator {

  template <typename T, template<typename> class VecType>
  void allocate(SysContentWithMEGV<T,VecType>& S, const VecType<T>& iX) {
    assert(IsValid(iX));
    release(S);
    typedef typename SysContentWithMEGV<T,VecType>::ParentType  Type;
    allocate(static_cast<Type&>(S),iX);
    imprint(S.Mass,iX);
    imprint(S.iMass,iX);
  }

}

#endif

