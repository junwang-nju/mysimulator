
#ifndef _System_Content_WithEGV_Refer_H_
#define _System_Content_WithEGV_Refer_H_

#include "system/content/with-egv/interface.h"
#include "system/content/with-eg/refer.h"

namespace mysimulator {

  template <typename T, template<typename> class VecType>
  void refer(SysContentWithEGV<T,VecType>& S, SysContentWithEGV<T,VecType>& rS,
             const int& partb, const int& parte, const int& newb) {
    assert(IsValid(rS));
    release(S);
    typedef typename SysContentWithEGV<T,VecType>::ParentType   Type;
    refer(static_cast<Type&>(S),static_cast<Type&>(rS),partb,parte,newb);
    allocate(S.Velocity);
    refer(S.Velocity(),rS.Velocity(),partb,parte,newb);
  }

}

#endif

