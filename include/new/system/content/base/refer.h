
#ifndef _System_Content_Base_Refer_H_
#define _System_Content_Base_Refer_H_

#include "system/content/base/interface.h"
#include "object/allocate.h"

namespace mysimulator {

  template <typename T, template<typename> class VT>
  void refer(SysContentBase<T,VT>& S, SysContentBase<T,VT>& rS,
             const int& partb, const int& parte, const int& newb) {
    assert(IsValid(rS));
    release(S);
    allocate(S.X);
    refer(S.X(),rS.X(),partb,parte,newb);
  }

  template <typename T, template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void refer(SCT<T,VT>& S, SCT<T,VT>& rS, const int& partb, const int& parte) {
    refer(S,rS,partb,parte,partb);
  }

}

#endif

