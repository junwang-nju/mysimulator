
#ifndef _System_Content_Data_E_Allocate_H_
#define _System_Content_Data_E_Allocate_H_

#include "system/content/data/e/interface.h"
#include "object/allocate.h"

namespace mysimulator {

  template <typename T>
  void allocate(SysContentDataE<T>& D) {
    release(D);
    allocate(D.Energy);
  }

  template <typename T, template<typename> class VT>
  void allocate(SysContentDataE<T>& D, const VT<T>&) { allocate(D); }

}

#endif

