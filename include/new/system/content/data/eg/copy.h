
#ifndef _System_Content_Data_EG_Copy_H_
#define _System_Content_Data_EG_Copy_H_

#include "system/content/data/eg/interface.h"
#include "object/copy.h"

namespace mysimulator {

  template <typename T, template<typename> class VT>
  void copy(SysContentDataEG<T,VT>& D, const SysContentDataEG<T,VT>& cD) {
    assert(IsValid(D)&&IsValid(cD));
    copy(D.Energy,cD.Energy);
    copy(D.Gradient,cD.Gradient);
  }

}

#endif

