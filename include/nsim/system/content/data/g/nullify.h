
#ifndef _System_Content_Data_G_Nullify_H_
#define _System_Content_Data_G_Nullify_H_

#include "system/content/data/g/interface.h"
#include "array/2d/fill.h"

namespace mysimulator {

  template <typename T>
  void NullifyEnergy(SystemContentDataG<T>&) {
    fprintf(stderr,"Not Available!\n");
  }

  template <typename T>
  void NullifyGradient(SystemContentDataG<T>& D) {
    assert(D.IsValid());
    Fill(D.Gradient,0.);
  }

  template <typename T>
  void NullifyBoth(SystemContentDataG<T>&) {
    fprintf(stderr,"Not Available!\n");
  }

  template <typename T>
  void Nullify(SystemContentDataG<T>& D) { NullifyGradient(D); }

}

#endif

