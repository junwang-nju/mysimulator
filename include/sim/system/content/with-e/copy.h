
#ifndef _System_Content_WithE_Copy_H_
#define _System_Content_WithE_Copy_H_

#include "system/content/with-e/interface.h"
#include "system/content/base/copy.h"
#include "system/content/data/e/copy.h"

namespace mysimulator {

  template <typename T>
  void Copy(SystemContentWithE<T>& C,const SystemContentWithE<T>& iC) {
    Copy(C.EGData,iC.EGData);
    typedef typename SystemContentWithE<T>::ParentType  Type;
    Copy(static_cast<Type&>(C),static_cast<const Type&>(iC));
  }

}

#endif

