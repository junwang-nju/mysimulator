
#ifndef _System_Content_Data_EG_Nullify_H_
#define _System_Content_Data_EG_Nullify_H_

#include "system/content/data/eg/interface.h"
#include "array/2d/fill.h"

namespace mysimulator {

  template <typename T>
  void NullifyEnergy(SystemContentDataEG<T>& D) {
    assert(D.IsValid());
    D.Energy[0]=0.;
  }

  template <typename T>
  void NullifyGradient(SystemContentDataEG<T>& D) {
    assert(D.IsValid());
    Fill(D.Gradient,0.);
  }

  template <typename T>
  void NullifyBoth(SystemContentDataEG<T>& D) {
    NullifyEnergy(D);
    NullifyGradient(D);
  }

  template <typename T>
  void Nullify(SystemContentDataEG<T>& D) { NullifyBoth(D); }

}

#endif

