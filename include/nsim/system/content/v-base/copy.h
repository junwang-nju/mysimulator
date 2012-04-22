
#ifndef _System_Content_VBase_Copy_H_
#define _System_Content_VBase_Copy_H_

#include "system/content/v-base/interface.h"
#include "array/2d/copy.h"

namespace mysimulator {

  template <typename T,template<typename>class EGType>
  void Copy(SystemContentVBase<T,EGType>& C,
            const SystemContentVBase<T,EGType>& iC) {
    Copy(C.Velocity,iC.Velocity);
    typedef typename SystemContentVBase<T,EGType>::ParentType   Type;
    Copy(static_cast<Type&>(C),static_cast<const Type&>(iC));
  }

}

#endif

