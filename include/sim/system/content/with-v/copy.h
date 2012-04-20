
#ifndef _System_Content_WithV_Copy_H_
#define _System_Content_WithV_Copy_H_

#include "system/content/with-v/interface.h"
#include "system/content/base/copy.h"

namespace mysimulator {

  template <typename T>
  void Copy(SystemContentWithV<T>& C,const SystemContentWithV<T>& iC) {
    Copy(C.Velocity,iC.Velocity);
    typedef typename SystemContentWithV<T>::ParentType  Type;
    Copy(static_cast<Type&>(C),static_cast<const Type&>(iC));
  }

}

#endif

