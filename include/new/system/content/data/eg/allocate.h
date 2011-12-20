
#ifndef _System_Content_Data_EG_Allocate_H_
#define _System_Content_Data_EG_Allocate_H_

#include "system/content/data/eg/interface.h"
#include "object/allocate.h"

namespace mysimulator {

  template <typename T, template<typename> class VT, typename T1>
  void allocate(SysContentDataEG<T,VT>& D, const VT<T1>& X) {
    assert(IsValid(X));
    release(D);
    allocate(D.Energy);
    _imprint_structure(D.Gradient,X);
  }

  template <typename T, template<typename> class VT, typename T1>
  void allocate(SysContentDataEG<T,VT>& D, const Object<VT<T1> >& X) {
    assert(IsValid(X));
    allocate(D,X());
  }

}

#endif

