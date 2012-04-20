
#ifndef _System_Content_WithEGV_Copy_H_
#define _System_Content_WithEGV_Copy_H_

#include "system/content/with-egv/interface.h"
#include "system/content/with-eg/copy.h"

namespace mysimulator {

  template <typename T>
  void Copy(SystemContentWithEGV<T>& C,const SystemContentWithEGV<T>& iC) {
    Copy(C.Velocity,iC.Velocity);
    typedef typename SystemContentWithEGV<T>::ParentType  Type;
    Copy(static_cast<Type&>(C),static_cast<const Type&>(iC));
  }

}

#endif

