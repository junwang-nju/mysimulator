
#ifndef _System_Content_Data_EG_Append_H_
#define _System_Content_Data_EG_Append_H_

#include "system/content/data/eg/interface.h"
#include "array/2d/shift.h"

namespace mysimulator {

  template <typename T>
  void AppendEnergy(SystemContentDataEG<T>& D,const SystemContentDataEG<T>& iD){
    assert(D.IsValid()&&iD.IsValid());
    D.Energy[0]+=iD.Energy[0];
  }

  template <typename T>
  void AppendGradient(SystemContentDataEG<T>&D,const SystemContentDataEG<T>&E) {
    assert(D.IsValid()&&E.IsValid());
    Shift(D.Gradient,E.Gradient);
  }

  template <typename T>
  void AppendBoth(SystemContentDataEG<T>& D,const SystemContentDataEG<T>& iD) {
    AppendEnergy(D,iD);
    AppendGradient(D,iD);
  }

  template <typename T>
  void Append(SystemContentDataEG<T>& D,const SystemContentDataEG<T>& iD) {
    AppendBoth(D,iD);
  }

}

#endif

