
#ifndef _System_Content_WithEG_Refer_H_
#define _System_Content_WithEG_Refer_H_

#include "system/content/with-eg/interface.h"
#include "system/content/base/refer.h"
#include "system/content/data/eg/refer.h"

namespace mysimulator {

  template <typename T, template<typename> class VT>
  void refer(SysContentWithEG<T,VT>& S, SysContentWithEG<T,VT>& rS,
             const int& partb, const int& parte, const int& newb) {
    assert(IsValid(rS));
    release(S);
    typedef typename SysContentWithEG<T,VT>::ParentType   Type;
    refer(static_cast<Type&>(S),static_cast<Type&>(rS),partb,parte,newb);
    refer(S.EGData,rS.EGData,partb,parte,newb);
  }

}

#endif

