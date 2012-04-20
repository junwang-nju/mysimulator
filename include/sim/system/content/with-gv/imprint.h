
#ifndef _System_Content_WithGV_Imprint_H_
#define _System_Content_WithGV_Imprint_H_

#include "system/content/with-gv/interface.h"
#include "system/content/with-g/imprint.h"

namespace mysimulator {

  template <typename T>
  void imprint(SystemContentWithGV<T>& C,const SystemContentWithGV<T>& iC) {
    release(C);
    imprint(C.Velocity,iC.Velocity);
    typedef typename SystemContentWithGV<T>::ParentType   Type;
    imprint(static_cast<Type&>(C),static_cast<const Type&>(iC));
  }

}

#endif

