
#ifndef _System_Content_Base_Interface_H_
#define _System_Content_Base_Interface_H_

#include "system/content/base/interface.h"
#include "array/2d/imprint.h"

namespace mysimulator {

  template <typename T>
  void Imprint(SystemContentBase<T>& C,const SystemContentBase<T>& iC) {
    release(C);
    Imprint(C.X,iC.X);
  }

  template <typename T>
  void ImprintStructure(SystemContentBase<T>& C,const SystemContentBase<T>& iC){
    release(C);
    ImprintStructure(C.X,iC.X);
  }

}

#endif

