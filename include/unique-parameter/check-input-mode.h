
#ifndef _Unique_Parameter_Check_Input_Mode_H_
#define _Unique_Parameter_Check_Input_Mode_H_

#include "io/input/interface.h"
#include "unique-parameter/input-mode-name.h"
#include <cctype>

namespace mysimulator {

  UniqueParameterInputModeName _CheckInputMode(InputBase& is) {
    char flag='\n';
    while(isspace(flag))    is>>flag;
    UniqueParameterInputModeName im;
    if(flag=='[') im=VectorMode;
    else { is.unget(flag); im=ValueMode; }
    return im;
  }

}

#endif

