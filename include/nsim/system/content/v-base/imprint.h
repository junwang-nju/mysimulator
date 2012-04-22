
#ifndef _System_Content_VBase_Imprint_H_
#define _System_Content_VBase_Imprint_H_

#include "system/content/v-base/interface.h"
#include "array/2d/imprint.h"

namespace mysimulator {

  template <typename T,template<typename>class EGType>
  void Imprint(SystemContentVBase<T,EGType>& C,
               const SystemContentVBase<T,EGType>& iC) {
    Imprint(C.Velocity,iC.Velocity);
    typedef typename SystemContentVBase<T,EGType>::ParentType Type;
    Imprint(static_cast<Type&>(C),static_cast<const Type&>(iC));
  }

}

#endif

