
#ifndef _Parameter_List_Input_Output_H_
#define _Parameter_List_Input_Output_H_

#include "data/derived/parameter-list.h"
#include "operation/derived/parameter-key-io.h"
#include "operation/basic/unique-parameter-io.h"

namespace std {

  InputBase& operator>>(InputBase& is, ParameterList& L) {
    assert(IsAvailable(L));
    for(unsigned int i=0;i<L.size;++i)  is>>L.key[i]>>L.value[i];
    L.update();
    return is;
  }

}

#endif

