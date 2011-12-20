
#ifndef _System_Content_Data_Energy_Nullify_H_
#define _System_Content_Data_Energy_Nullify_H_

#include "system/content/data/e/interface.h"
#include "intrinsic-type/constant.h"

namespace mysimulator {

  template <typename T>
  void nullifyEnergy(SysContentDataE<T>& D) {
    assert(IsValid(D));
    copy(D.Energy(),cZero);
  }

  template <typename T>
  void nullifyGradient(SysContentDataE<T>&) {
    Error("No availbale for this data!");
  }

  template <typename T>
  void nullifyBoth(SysContentDataE<T>&) {
    Error("No availbale for this data!");
  }

  template <typename T>
  void nullify(SysContentDataE<T>& D) { nullifyEnergy(D); }

}

#endif

