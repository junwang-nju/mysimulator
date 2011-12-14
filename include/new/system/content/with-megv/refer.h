
#ifndef _System_Content_WithMEGV_Refer_H_
#define _System_Content_WithMEGV_Refer_H_

#include "system/content/with-megv/interface.h"
#include "system/content/with-egv/refer.h"

namespace mysimulator {

  template <typename T, template<typename> class VecType>
  void refer(SysContentWithMEGV<T,VecType>& S,SysContentWithMEGV<T,VecType>& rS,
             const int& partb, const int& parte, const int& newb) {
    assert(IsValid(rS));
    release(S);
    typedef typename SysContentWithMEGV<T,VecType>::ParentType    Type;
    refer(static_cast<Type&>(S),static_cast<Type&>(rS),partb,parte,newb);
    refer(S.Mass(),rS.Mass(),partb,parte,newb);
    refer(S.iMass(),rS.iMass(),partb,parte,newb);
  }

}

#endif

