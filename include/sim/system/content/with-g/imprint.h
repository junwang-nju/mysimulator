
#ifndef _System_Content_WithG_Imprint_H_
#define _System_Content_WithG_Imprint_H_

#include "system/content/with-g/interface.h"
#include "system/content/base/imprint.h"
#include "system/content/data/g/imprint.h"

namespace mysimulator {

  template <typename T>
  void imprint(SystemContentWithG<T>& C, const SystemContentWithG<T>& iC) {
    release(C);
    imprint(C.EGData,iC.EGData);
    typedef typename SystemContentWithG<T>::ParentType  Type;
    imprint(static_cast<Type&>(C),static_cast<const Type&>(iC));
  }

}

#endif

