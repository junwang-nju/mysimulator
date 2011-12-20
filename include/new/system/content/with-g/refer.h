
#ifndef _System_Content_WithG_Refer_H_
#define _System_Content_WithG_Refer_H_

#include "system/content/with-g/interface.h"
#include "system/content/base/refer.h"
#include "system/content/data/g/refer.h"

namespace mysimulator {

  template <typename T, template<typename> class VT>
  void refer(SysContentWithG<T,VT>& S, SysContentWithG<T,VT>& rS,
             const int& partb, const int& parte, const int& newb) {
    assert(IsValid(rS));
    release(S);
    typedef typename SysContentWithG<T,VT>::ParentType  Type;
    refer(static_cast<Type&>(S),static_cast<Type&>(rS),partb,parte,newb);
    refer(S.EGData,rS.EGData,partb,parte,newb);
  }

}

#endif

