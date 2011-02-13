
#ifndef _Parameter_Key_Input_Output_H_
#define _Parameter_Key_Input_Output_H_

#include "data/derived/parameter-key.h"
#include "operation/basic/vector-io.h"

namespace std {

  InputBase& operator>>(InputBase& is, ParameterKey& K) {
    is>>static_cast<Vector<unsigned int>&>(K); K.update(); return is;
  }

}

#endif

