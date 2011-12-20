
#ifndef _System_Content_Data_Gradient_Accumulate_H_
#define _System_Content_Data_Gradient_Accumulate_H_

#include "system/content/data/g/interface.h"
#include "intrinsic-type/constant.h"

namespace mysimulator {

  template <typename T, template<typename> class VT>
  void accumulateEnergy(SysContentDataG<T,VT>&,const SysContentDataG<T,VT>&) {
    Error("Not available for this data!");
  }

  template <typename T, template<typename> class VT>
  void accumulateGradient(SysContentDataG<T,VT>& D,
                          const SysContentDataG<T,VT>& aD) {
    assert(IsValid(D)&&IsValid(aD));
    shift(D.Gradient(),cOne,aD.Gradient());
  }

  template <typename T, template<typename> class VT>
  void accumulateBoth(SysContentDataG<T,VT>&,const SysContentDataG<T,VT>&) {
    Error("Not available for this data!");
  }

  template <typename T, template<typename> class VT>
  void accumulate(SysContentDataG<T,VT>& D, const SysContentDataG<T,VT>& aD) {
    accumulateGradient(D,aD);
  }

}

#endif

