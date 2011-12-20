
#ifndef _System_Content_Data_EG_Refer_H_
#define _System_Content_Data_EG_Refer_H_

#include "system/content/data/eg/interface.h"
#include "object/allocate.h"
#include "object/refer.h"

namespace mysimulator {

  template <typename T, template<typename> class VT>
  void refer(SysContentDataEG<T,VT>& D, SysContentDataEG<T,VT>& rD,
             const int& partb, const int& parte, const int& newb) {
    assert(IsValid(rD));
    release(D);
    refer(D.Energy,rD.Energy);
    allocate(D.Gradient);
    refer(D.Gradient(),rD.Gradient(),partb,parte,newb);
  }

  template <typename T, template<typename> class VT>
  void refer(SysContentDataEG<T,VT>& D, SysContentDataEG<T,VT>& rD,
             const int& partb, const int& parte) {
    refer(D,rD,partb,parte,partb);
  }

}

#endif

