
#ifndef _InputOutput_Input_String_Copy_H_
#define _InputOutput_Input_String_Copy_H_

#include "io/input/string/interface.h"
#include "vector/copy.h"
#include "io/input/copy.h"
#include <cstring>

namespace mysimulator {

  void copy(StringInput& I, const Vector<char>& bf) {
    assert(IsValid(bf));
    I.open(bf.size);
    copy(I.buffer,bf);
  }

  void copy(StringInput& I, const char* p, const unsigned int n) {
    I.open(n);
    strncpy(I.buffer(),p,n-1);
  }

  void copy(StringInput& I, const StringInput& cI) {
    assert(IsValid(cI));
    I.open(cI.buffer.size);
    copy(I.buffer,cI.buffer);
    copy(I.property,cI.property);
    copy(static_cast<InputBase&>(I),static_cast<const InputBase&>(cI));
  }

}

#endif

