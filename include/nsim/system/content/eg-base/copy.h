
#ifndef _System_Content_EGBase_Copy_H_
#define _System_Content_EGBase_Copy_H_

#include "system/content/eg-base/interface.h"
#include "system/content/base/copy.h"

namespace mysimulator {

  template <typename T,template<typename>class EGDataType>
  void Copy(SystemContentEGBase<T,EGDataType>& C,
            const SystemContentEGBase<T,EGDataType>& iC) {
    Copy(C.EGData,iC.EGData);
    typedef typename SystemContentEGBase<T,EGDataType>::ParentType  Type;
    Copy(static_cast<Type&>(C),static_cast<const Type&>(iC));
  }

}

#endif

