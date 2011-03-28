
#ifndef _Vector_InputOutput_H_
#define _Vector_InputOutput_H_

#include "vector/interface.h"

namespace mysimulator {

  template <typename T>
  OutputBase& operator<<(OutputBase& O, const Vector<T>& v) {
    assert(IsValid(v));
    O<<v[0];
    for(unsigned int i=1;i<v.size;++i)  O<<"\t"<<v[i];
    return O;
  }

  OutputBase& operator<<(OutputBase& O, const Vector<char>& v) {
    assert(IsValid(v));
    for(unsigned int i=0;i<v.size;++i)  O<<v[i];
    return O;
  }

  template <typename T>
  InputBase& operator>>(InputBase& I, Vector<T>& v) {
    assert(IsValid(v));
    for(unsigned int i=0;i<v.size;++i)  I>>v[i];
    return I;
  }

}

#endif

