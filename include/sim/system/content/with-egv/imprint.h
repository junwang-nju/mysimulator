
#ifndef _System_Content_WithEGV_Imprint_H_
#define _System_Content_WithEGV_Imprint_H_

#include "system/content/with-egv/interface.h"
#include "system/content/with-eg/imprint.h"

namespace mysimulator {

  template <typename T>
  void imprint(SystemContentWithEGV<T>& C,const SystemContentWithEGV<T>& iC) {
    release(C);
    imprint(C.Velocity,iC.Velocity);
    typedef typename SystemContentWithEGV<T>::ParentType  Type;
    imprint(static_cast<Type&>(C),static_cast<const Type&>(iC));
  }

}

#endif

