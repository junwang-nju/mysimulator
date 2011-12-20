
#ifndef _System_Content_WithGV_Refer_H_
#define _System_Content_WithGV_Refer_H_

#include "system/content/with-gv/interface.h"
#include "system/content/with-g/refer.h"

namespace mysimulator {

  template <typename T, template<typename> class VT>
  void refer(SysContentWithGV<T,VT>& S, SysContentWithGV<T,VT>& rS,
             const int& partb, const int& partb, const int& newb) {
    assert(IsValid(rS));
    release(S);
    typedef typename SysContentWithGV<T,VT>::ParentType   Type;
    refer(static_cast<Type&>(S),static_cast<Type&>(rS),partb,parte,newb);
    allocate(S.Velocity);
    refer(S.Velocity(),rS.Velocity(),partb,parte,newb);
  }

}

#endif

