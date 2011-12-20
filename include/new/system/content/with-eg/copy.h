
#ifndef _System_Content_WithEG_Copy_H_
#define _System_Content_WithEG_Copy_H_

#include "system/content/with-eg/interface.h"
#include "system/content/base/copy.h"
#include "system/content/data/eg/copy.h"

namespace mysimulator {

  template <typename T, template<typename> class VT>
  void copy(SysContentWithEG<T,VT>& S, const SysContentWithEG<T,VT>& cS) {
    assert(IsValid(S)&&IsValid(cS));
    typedef typename SysContentWithEG<T,VT>::ParentType Type;
    copy(static_cast<Type&>(S),static_cast<const Type&>(cS));
    copy(S.EGData,cS.EGData);
  }

}

#endif

