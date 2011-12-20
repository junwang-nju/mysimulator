
#ifndef _System_Content_Data_EG_Nullify_H_
#define _System_Content_Data_EG_Nullify_H_

#include "system/content/data/eg/interface.h"
#include "intrinsic-type/constant.h"

namespace mysimulator {

  template <typename T, template <typename> class VT>
  void nullifyEnergy(SysContentDataEG<T,VT>& D) {
    assert(IsValid(D));
    copy(D.Energy(),cZero);
  }

  template <typename T, template <typename> class VT>
  void nullifyGradient(SysContentDataEG<T,VT>& D) {
    assert(IsValid(D));
    fill(D.Gradient(),cZero);
  }

  template <typename T, template <typename> class VT>
  void nullifyBoth(SysContentDataEG<T,VT>& D) {
    assert(IsValid(D));
    copy(D.Energy(),cZero);
    fill(D.Gradient(),cZero);
  }

  template <typename T, template <typename> class VT>
  void nullify(SysContentDataEG<T,VT>& D) { nullifyBoth(D); }

}

#endif

