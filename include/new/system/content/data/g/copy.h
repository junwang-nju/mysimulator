
#ifndef _System_Content_Data_G_Copy_H_
#define _System_Content_Data_G_Copy_H_

#include "system/content/data/g/interface.h"
#include "object/copy.h"

namespace mysimulator {

  template <typename T, template<typename> class VT>
  void copy(SysContentDataG<T,VT>& D, const SysContentDataG<T,VT>& cD) {
    assert(IsValid(D)&&IsValid(cD));
    copy(D.Gradient,cD.Gradient);
  }

}

#endif

