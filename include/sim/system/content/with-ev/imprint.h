
#ifndef _System_Content_WithEV_Imprint_H_
#define _System_Content_WithEV_Imprint_H_

#include "system/content/with-ev/interface.h"
#include "system/content/with-e/imprint.h"

namespace mysimulator {

  template <typename T>
  void imprint(SystemContentWithEV<T>& C,const SystemContentWithEV<T>& iC) {
    release(C);
    imprint(C.Velocity,iC.Velocity);
    typedef typename SystemContentWithEV<T>::ParentType Type;
    imprint(static_cast<Type&>(C),static_cast<const Type&>(iC));
  }

}

#endif

