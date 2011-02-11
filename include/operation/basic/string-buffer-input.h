
#ifndef _String_Buffer_Input_H_
#define _String_Buffer_Input_H_

#include "operation/basic/input-base.h"
#include "data/name/vector.h"
#include <cstdio>
#include <cassert>

namespace std {

  struct StringInput;
  void release(StringInput&);
  void copy(StringInput&, const Vector<char>&);
  void copy(StringInput&, const char*, const unsigned int);
  
  struct StringInput : public InputBase {
    Vector<char> buffer;
    Vector<unsigned int> property;
    StringInput() : buffer(), property() {}
    StringInput(const Vector<char>& bf) : buffer(), property() {
      copy(*this,bf);
    }
    StringInput(const char* ptr, const unsigned int n) : buffer(), property() {
      copy(*this,ptr,n);
    }
    StringInput(const StringInput&) {
      fprintf(stderr,"Cannot create String Input");
      exit(0);
    }
    StringInput& operator=(const StringInput&) {
      fprintf(stderr,"Cannot copy String Input");
      exit(0);
      return *this;
    }
    ~StringInput() { release(*this); }
  };

}

#endif
