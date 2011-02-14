
#ifndef _Property_List_Input_Output_H_
#define _Property_List_Input_Output_H_

#include "data/basic/property-list.h"
#include "operation/basic/vector-io.h"

namespace std {

  template <typename T>
  OutputBase& operator<<(OutputBase& os, const PropertyList<T>& L) {
    assert(IsAvailable(L));
    os<<L[0];
    for(unsigned int k=1;k<L.nunit;++k) os<<Endl<<L[k];
    return os;
  }

}

#endif

