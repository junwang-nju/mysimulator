
#ifndef _System_Content_Base_Refer_H_
#define _System_Content_Base_Refer_H_

#include "system/content/base/interface.h"
#include "object/allocate.h"

namespace mysimulator {

  template <typename T, template<typename> class VecType>
  void refer(SysContentBase<T,VecType>& S, SysContentBase<T,VecType>& rS,
             const int& partb, const int& parte, const int newb) {
    assert(IsValid(rS));
    release(S);
    allocate(S.X);
    refer(S.X(),rS.X(),partb,parte,newb);
  }

  template <typename T, template<typename> class VecType,
            template<typename,template<typename>class> class SysContentType>
  void refer(SysContentType<T,VecType>& S, SysContentType<T,VecType>& rS,
             const int& partb, const int& parte) {
    refer(S,rS,partb,parte,partb);
  }

}

#endif

