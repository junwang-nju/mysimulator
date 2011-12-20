
#ifndef _System_Content_Data_Gradient_Nullify_H_
#define _System_Content_Data_Gradient_Nullify_H_

#include "system/content/data/g/interface.h"
#include "intrinsic-type/constant.h"

namespace mysimulator {

  template <typename T, template <typename> class VT>
  void nullifyEnergy(SysContentDataG<T,VT>&) {
    Error("Not available for this data!");
  }

  template <typename T, template <typename> class VT>
  void nullifyGradient(SysContentDataG<T,VT>& D) {
    assert(IsValid(D));
    fill(D.Gradient(),cZero);
  }

  template <typename T, template <typename> class VT>
  void nullifyBoth(SysContentDataG<T,VT>&) {
    Error("Not available for this data!");
  }

  template <typename T, template <typename> class VT>
  void nullify(SysContentDataG<T,VT>& D) { nullifyGradient(D); }

}

#endif

