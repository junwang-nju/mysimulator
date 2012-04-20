
#ifndef _System_Content_WithE_Imprint_H_
#define _System_Content_WithE_Imprint_H_

#include "system/content/with-e/interface.h"
#include "system/content/base/imprint.h"
#include "system/content/data/e/imprint.h"

namespace mysimulator {

  template <typename T>
  void imprint(SystemContentWithE<T>& C, const SystemContentWithE<T>& iC) {
    release(C);
    imprint(C.EGData,iC.EGData);
    typedef typename SystemContentWithE<T>::ParentType Type;
    imprint(static_cast<Type&>(C),static_cast<const Type&>(iC));
  }

}

#endif

