
#ifndef _System_Content_EGBase_Imprint_H_
#define _System_Content_EGBase_Imprint_H_

#include "system/content/eg-base/interface.h"
#include "system/content/base/imprint.h"

namespace mysimulator {

  template <typename T,template<typename> class EGDataType>
  void Imprint(SystemContentEGBase<T,EGDataType>& C,
               const SystemContentEGBase<T,EGDataType>& iC) {
    C.Clear();
    Imprint(C.EGData,iC.EGData);
    typedef typename SystemContentEGBase<T,EGDataType>::ParentType Type;
    Imprint(static_cast<Type&>(C),static_cast<const Type&>(iC));
  }

}

#endif

