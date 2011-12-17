
#ifndef _System_Content_WithEV_Refer_H_
#define _System_Content_WithEV_Refer_H_

#include "system/content/with-ev/interface.h"
#include "system/content/with-e/refer.h"

namespace mysimulator {

  template <typename T, template<typename> class VT>
  void refer(SysContentWithEV<T,VT>& S, SysContentWithEV<T,VT>& rS,
             const int& partb, const int& parte, const int& newb) {
    assert(IsValid(rS));
    release(S);
    typedef typename SysContentWithEV<T,VT>::ParentType   Type;
    refer(static_cast<Type&>(S),static_cast<Type&>(rS),partb,parte,newb);
    allocate(S.Velocity);
    refer(S.Velocity(),rS.Velocity(),partb,parte,newb);
  }

}

#endif

