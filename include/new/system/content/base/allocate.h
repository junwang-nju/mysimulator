
#ifndef _System_Content_Base_Allocate_H_
#define _System_Content_Base_Allocate_H_

#include "system/content/base/interface.h"
#include "object/allocate.h"

namespace mysimulator {

  template <typename T, template<typename> class VecType>
  void allocate(SysContentBase<T,VecType>& S, const VecType<T>& iX) {
    assert(IsValid(iX));
    release(S);
    imprint(S.X,iX);
  }

  template <typename T, template<typename> class VecType,
            template<typename,template<typename>class> class SysContentType>
  void allocate(SysContentType<T,VecType>& S, const Object<VecType<T> >& iX) {
    assert(IsValid(iX));
    allocate(S,iX());
  }

}

#endif

