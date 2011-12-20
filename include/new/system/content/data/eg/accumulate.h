
#ifndef _System_Content_Data_EG_Accumulate_H_
#define _System_Content_Data_EG_Accumulate_H_

#include "system/content/data/eg/interface.h"
#include "intrinsic-type/constant.h"

namespace mysimulator {

  template <typename T, template<typename> class VT>
  void accumulateEnergy(SysContentDataEG<T,VT>& D,
                        const SysContentDataEG<T,VT>& aD) {
    assert(IsValid(D)&&IsValid(aD));
    D.Energy()+=aD.Energy();
  }

  template <typename T, template<typename> class VT>
  void accumulateGradient(SysContentDataEG<T,VT>& D,
                          const SysContentDataEG<T,VT>& aD) {
    assert(IsValid(D)&&IsValid(aD));
    shift(D.Gradient(),cOne,aD.Gradient());
  }

  template <typename T, template<typename> class VT>
  void accumulateBoth(SysContentDataEG<T,VT>& D,
                      const SysContentDataEG<T,VT>& aD) {
    assert(IsValid(D)&&IsValid(aD));
    D.Energy()+=aD.Energy();
    shift(D.Gradient(),cOne,aD.Gradient());
  }

  template <typename T, template<typename> class VT>
  void accumulate(SysContentDataEG<T,VT>& D, const SysContentDataEG<T,VT>& aD) {
    accumulateBoth(D,aD);
  }

}

#endif

