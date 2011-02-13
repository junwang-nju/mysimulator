
#ifndef _Unique_Parameter_Input_Output_H_
#define _Unique_Parameter_Input_Output_H_

#include "data/basic/unique-parameter.h"
#include "data/basic/input-base.h"
#include "data/basic/output-base.h"

namespace std {

  InputBase& operator>>(InputBase& is, UniqueParameter& P) {
    static char flag;
    is>>flag;
    if((flag=='D')||(flag=='d'))  is>>P.d;
    else if((flag='F')||(flag=='f'))  is>>P.f;
    else if((flag='U')||(flag=='u'))  is>>P.u;
    else if((flag='I')||(flag=='i'))  is>>P.i;
    else if((flag='P')||(flag=='P'))  is>>P.ptr;
    else if(isdigit(flag)||(flag=='+')) { is.unget(flag); is>>P.ull; }
    else is.SetState(FailBit);
    return is;
  }

  OutputBase& operator<<(OutputBase& os, const UniqueParameter& P) {
    os<<P.ull;
    return os;
  }

}

#endif

