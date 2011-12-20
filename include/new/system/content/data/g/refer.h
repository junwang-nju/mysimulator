
#ifndef _System_Content_Data_G_Refer_H_
#define _System_Content_Data_G_Refer_H_

#include "system/content/data/g/interface.h"
#include "object/allocate.h"

namespace mysimulator {

  template <typename T, template<typename> class VT>
  void refer(SysContentDataG<T,VT>& D, SysContentDataG<T,VT>& rD,
             const int& partb, const int& parte, const int& newb) {
    assert(IsValid(rD));
    release(D);
    allocate(D.Gradient);
    refer(D.Gradient(),rD.Gradient(),partb,parte,newb);
  }

  template <typename T, template<typename> class VT>
  void refer(SysContentDataG<T,VT>& D, SysContentDataG<T,VT>& rD,
             const int& partb, const int& parte) {
    refer(D,rD,partb,parte,partb);
  }

}

#endif

