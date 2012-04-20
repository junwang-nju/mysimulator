
#ifndef _System_Content_WithV_Imprint_H_
#define _System_Content_WithV_Imprint_H_

#include "system/content/with-v/interface.h"
#include "system/content/base/imprint.h"

namespace mysimulator {

  template <typename T>
  void imprint(SystemContentWithV<T>& C,const SystemContentWithV<T>& iC) {
    release(C);
    imprint(C.Velocity,iC.Velocity);
    typedef typename SystemContentWithV<T>::ParentType  Type;
    imprint(static_cast<Type&>(C),static_cast<const Type&>(iC));
  }

}

#endif

