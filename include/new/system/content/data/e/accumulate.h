
#ifndef _System_Content_Data_Energy_Accumulate_H_
#define _System_Content_Data_Energy_Accumulate_H_

#include "system/content/data/e/interface.h"
#include "io/error.h"

namespace mysimulator {

  template <typename T>
  void accumulateEnergy(SysContentDataE<T>& D, const SysContentDataE<T>& aD) {
    assert(IsValid(D)&&IsValid(aD));
    D.Energy()+=aD.Energy();
  }

  template <typename T>
  void accumulateGradient(SysContentDataE<T>&,const SysContentDataE<T>&) {
    Error("Not available for this data!");
  }

  template <typename T>
  void accumulateBoth(SysContentDataE<T>&,const SysContentDataE<T>&) {
    Error("Not available for this data!");
  }

  template <typename T>
  void accumulate(SysContentDataE<T>& D, const SysContentDataE<T>& aD) {
    accumulateEnergy(D,aD);
  }

}

#endif

