
#ifndef _System_Content_WithEG_Copy_H_
#define _System_Content_WithEG_Copy_H_

#include "system/content/with-eg/interface.h"
#include "system/content/with-e/copy.h"

namespace mysimulator {

  template <typename T, template<typename> class VT>
  void copy(SysContentWithEG<T,VT>& S, const SysContentWithEG<T,VT>& rS) {
    assert(IsValid(S)&&IsValid(rS));
    typedef typename SysContentWithEG<T,VT>::ParentType Type;
    copy(static_cast<Type&>(S),static_cast<const Type&>(rS));
    copy(S.Gradient,rS.Gradient);
  }

}

#endif

