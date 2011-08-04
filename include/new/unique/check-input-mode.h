
#ifndef _Unique_Check_Input_Mode_H_
#define _Unique_Check_Input_Mode_H_

#include "io/input/base/interface.h"
#include "unique/input-mode-name.h"
#include <cctype>
#include <cassert>

namespace mysimulator {

  UniqueInputModeName _InputMode(InputBase& is) {
    assert(IsValid(is));
    char flag='\n';
    while(isspace(flag))  is>>flag;
    UniqueInputModeName im;
    if(flag=='[')   im=VectorMode;
    else { is.unget(flag); im=ValueMode; }
    return im;
  }

}

#endif

