
#ifndef _System_Content_WithEV_Copy_H_
#define _System_Content_WithEV_Copy_H_

#include "system/content/with-ev/interface.h"
#include "system/content/with-e/copy.h"

namespace mysimulator {

  template <typename T>
  void Copy(SystemContentWithEV<T>& C,const SystemContentWithEV<T>& iC) {
    Copy(C.Velocity,iC.Velocity);
    typedef typename SystemContentWithEV<T>::ParentType Type;
    Copy(static_cast<Type&>(C),static_cast<const Type&>(iC));
  }

}

#endif

