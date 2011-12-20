
#ifndef _System_Content_WithV_Refer_H_
#define _System_Content_WithV_Refer_H_

#include "system/content/with-v/interface.h"
#include "system/content/base/refer.h"

namespace mysimulator {

  template <typename T, template<typename> class VT>
  void refer(SysContentWithV<T,VT>& S, SysContentWithV<T,VT>& rS,
             const int& partb, const int& parte, const int& newb) {
    assert(IsValid(rS));
    release(S);
    typedef typename SysContentWithV<T,VT>::ParentType  Type;
    refer(static_cast<Type&>(S),static_cast<Type&>(rS),partb,parte,newb);
    allocate(S.Velocity);
    refer(S.Velocity(),rS.Velocity(),partb,parte,newb);
  }

}

#endif

