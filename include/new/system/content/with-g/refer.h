
#ifndef _System_Content_WithG_Refer_H_
#define _System_Content_WithG_Refer_H_

#include "system/content/with-g/interface.h"
#include "system/content/base/refer.h"

namespace mysimulator {

  template <typename T, template<typename> class VecType>
  void refer(SysContentWithG<T,VecType>& S, SysContentWithG<T,VecType>& rS,
             const int& partb, const int& parte, const int& newb) {
    assert(IsValid(rS));
    release(S);
    typedef typename SysContentWithG<T,VecType>::ParentType Type;
    refer(static_cast<Type&>(S),static_cast<Type&>(rS),partb,parte,newb);
    refer(S.Gradient(),rS.Gradient(),partb,parte,newb);
  }

}

#endif

