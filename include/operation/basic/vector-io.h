
#ifndef _Vector_Input_Output_H_
#define _Vector_Input_Output_H_

#include "data/basic/vector.h"
#include "data/basic/output-base.h"
#include "data/basic/input-base.h"

namespace std {

  template <typename T>
  OutputBase& operator<<(OutputBase& os, const Vector<T>& v) {
    assert(IsAvailable(v));
    os<<v[0];
    for(unsigned int i=1;i<v.size;++i)  os<<"\t"<<v[i];
    return os;
  }

  OutputBase& operator<<(OutputBase& os, const Vector<char>& v) {
    assert(IsAvailable(v));
    for(unsigned int i=0;i<v.size;++i)  os<<v[i];
    return os;
  }

  template <typename T>
  InputBase& operator>>(InputBase& is, Vector<T>& v) {
    assert(IsAvailable(v));
    for(unsigned int i=0;i<v.size;++i)  is>>v[i];
    return is;
  }

}

#endif

