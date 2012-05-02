
#ifndef _System_Content_Data_NULL_Nullify_H_
#define _System_Content_Data_NULL_Nullify_H_

#include "system/content/data/null/interface.h"

namespace mysimulator {

  template <typename T>
  void NullifyEnergy(SystemContentDataNull<T>&) {
    fprintf(stderr,"Not Available!\n");
  }

  template <typename T>
  void NullifyGradient(SystemContentDataNull<T>&) {
    fprintf(stderr,"Not Available!\n");
  }

  template <typename T>
  void NullifyBoth(SystemContentDataNull<T>&) {
    fprintf(stderr,"Not Available!\n");
  }

  template <typename T>
  void Nullify(SystemContentDataNull<T>&) {
    fprintf(stderr,"Not Available!\n");
  }

}

#endif

