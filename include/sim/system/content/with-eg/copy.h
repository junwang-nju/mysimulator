
#ifndef _System_Content_WithEG_Copy_H_
#define _System_Content_WithEG_Copy_H_

#include "system/content/with-eg/interface.h"
#include "system/content/base/copy.h"
#include "system/content/data/eg/copy.h"

namespace mysimulator {

  template <typename T>
  void Copy(SystemContentWithEG<T>& C,const SystemContentWithEG<T>& iC) {
    Copy(C.EGData,iC.EGData);
    typedef typename SystemContentWithEG<T>::ParentType Type;
    Copy(static_cast<Type&>(C),static_cast<const Type&>(iC));
  }

}

#endif

