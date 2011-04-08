
#ifndef _List_InputOuput_H_
#define _List_InputOuput_H_

#include "list/interface.h"
#include "vector/io.h"

namespace mysimulator {

  template <typename T>
  OutputBase& operator<<(OutputBase& os, const List<T>& L) {
    assert(IsValid(L));
    os<<L[0];
    for(unsigned int k=0;k<L.ListSize();++k)  os<<Endl<<L[k];
    return os;
  }

}

#endif

