
#ifndef _Unique_Parameter_64bit_InputOutput_H_
#define _Unique_Parameter_64bit_InputOutput_H_

#include "unique-parameter/64bit/interface.h"
#include "io/input/interface.h"
#include "io/output/interface.h"

namespace mysimulator {

  InputBase& operator>>(InputBase& is, UniqueParameter64Bit& P) {
    char flag='\n';
    while(isspace(flag)) { is>>flag; }
    if((flag=='D')||(flag=='d'))  is>>P.d;
    else if((flag=='F')||(flag=='f'))   is>>P.f;
    else if((flag=='U')||(flag=='u'))   is>>P.u;
    else if((flag=='I')||(flag=='i'))   is>>P.i;
    else if((flag=='S')||(flag=='s'))   is>>P.s;
    else if((flag=='C')||(flag=='c'))   is>>P.c;
    else if((flag=='P')||(flag=='p'))   is>>P.ptr;
    else if(isdigit(flag)||(flag=='+')) { is.unget(flag); is>>P.ull; }
    else is.SetState(FailBit);
    return is;
  }

}

#endif

