
#ifndef _System_Content_WithG_Copy_H_
#define _System_Content_WithG_Copy_H_

#include "system/content/with-g/interface.h"
#include "system/content/base/copy.h"
#include "system/content/data/g/copy.h"

namespace mysimulator {

  template <typename T>
  void Copy(SystemContentWithG<T>& C,const SystemContentWithG<T>& iC) {
    Copy(C.EGData,iC.EGData);
    typedef typename SystemContentWithG<T>::ParentType  Type;
    Copy(static_cast<Type&>(C),static_cast<const Type&>(iC));
  }

}

#endif

