
#ifndef _Intrinsic_Type_String_H_
#define _Intrinsic_Type_String_H_

namespace mysimulator {

  unsigned int LineSize(const char* s) {
    unsigned int n=0;
    char* l=const_cast<char*>(s);
    while((*(l++))!='\n') ++n;
    return n;
  }

}

#endif

