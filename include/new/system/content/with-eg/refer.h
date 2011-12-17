
#ifndef _System_Content_WithEG_Refer_H_
#define _System_Content_WithEG_Refer_H_

#include "system/content/with-eg/interface.h"
#include "system/content/with-e/refer.h"

namespace mysimulator {

  template <typename T, template<typename> class VecType>
  void refer(SysContentWithEG<T,VecType>& S, SysContentWithEG<T,VecType>& rS,
             const int& partb, const int& parte, const int& newb) {
    assert(IsValid(rS));
    release(S);
    typedef typename SysContentWithEG<T,VecType>::ParentType  Type;
    refer(static_cast<Type&>(S),static_cast<Type&>(rS),partb,parte,newb);
    allocate(S.Gradient);
    refer(S.Gradient(),rS.Gradient(),partb,parte,newb);
  }

}

#endif

