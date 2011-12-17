
#ifndef _System_Content_WithE_Refer_H_
#define _System_Content_WithE_Refer_H_

#include "system/content/with-e/interface.h"
#include "system/content/base/refer.h"

namespace mysimulator {

  template <typename T, template<typename> class VecType>
  void refer(SysContentWithE<T,VecType>& S, SysContentWithE<T,VecType>& rS,
             const int& partb, const int& parte, const int& newb) {
    assert(IsValid(rS));
    release(S);
    typedef typename SysContentWithE<T,VecType>::ParentType Type;
    refer(static_cast<Type&>(S),static_cast<Type&>(rS),partb,parte,newb);
    refer(S.Energy,rS.Energy);
  }

}

#endif

