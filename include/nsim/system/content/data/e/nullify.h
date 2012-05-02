
#ifndef _System_Content_Data_E_Nullify_H_
#define _System_Content_Data_E_Nullify_H_

#include "system/content/data/e/interface.h"

namespace mysimulator {

  template <typename T>
  void NullifyEnergy(SystemContentDataE<T>& D) {
    assert(D.IsValid());
    D.Energy[0]=0;
  }

  template <typename T>
  void NullifyGradient(SystemContentDataE<T>&) {
    fprintf(stderr,"Not Available!\n");
  }

  template <typename T>
  void NullifyBoth(SystemContentDataE<T>&) {
    fprintf(stderr,"Not Available!\n");
  }

  template <typename T>
  void Nullify(SystemContentDataE<T>& D) { NullifyEnergy(D); }

}

#endif

