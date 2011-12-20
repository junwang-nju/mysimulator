
#ifndef _System_Content_Data_E_Refer_H_
#define _System_Content_Data_E_Refer_H_

#include "system/content/data/e/interface.h"
#include "object/refer.h"

namespace mysimulator {

  template <typename T>
  void refer(SysContentDataE<T>& D, SysContentDataE<T>& rD,
             const int&, const int&, const int&) {
    assert(IsValid(rD));
    release(D);
    refer(D.Energy,rD.Energy);
  }

  template <typename T>
  void refer(SysContentDataE<T>& D, SysContentDataE<T>& rD,
             const int&, const int&) { refer(D,rD,0,0,0); }

}

#endif

