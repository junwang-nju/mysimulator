
#ifndef _System_Content_WithEG_Imprint_H_
#define _System_Content_WithEG_Imprint_H_

#include "system/content/with-eg/interface.h"
#include "system/content/base/imprint.h"
#include "system/content/data/eg/imprint.h"

namespace mysimulator {

  template <typename T>
  void imprint(SystemContentWithEG<T>& C,const SystemContentWithEG<T>& iC) {
    release(C);
    imprint(C.EGData,iC.EGData);
    typedef typename SystemContentWithEG<T>::ParentType   Type;
    imprint(static_cast<Type&>(C),static_cast<const Type&>(iC));
  }

}

#endif

