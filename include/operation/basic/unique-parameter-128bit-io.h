
#ifndef _Unique_Parameter_128bit_Input_Output_H_
#define _Unique_Parameter_128bit_Input_Output_H_

#include "data/basic/unique-parameter-128bit.h"
#include "data/basic/input-base.h"
#include "data/basic/output-base.h"

namespace std {
  
    InputBase& operator>>(InputBase& is, UniqueParameter128b& P) {
    static char flag;
    static char buff[1024];
    is>>buff;
    flag=buff[0];
    if((flag=='G')||(flag=='g'))  is>>P.ld;
    else if((flag=='D')||(flag=='d')) is>>buff>>P.d[0]>>P.d[1]>>buff;
    else if((flag=='F')||(flag=='f'))
      is>>buff>>P.f[0]>>P.f[1]>>P.f[2]>>P.f[3]>>buff;
    else if((flag=='U')||(flag=='u'))
      is>>buff>>P.u[0]>>P.u[1]>>P.u[2]>>P.u[3]>>buff;
    else if((flag=='I')||(flag=='i'))
      is>>buff>>P.i[0]>>P.i[1]>>P.i[2]>>P.i[3]>>buff;
    else if((flag=='L')||(flag=='l')) is>>buff>>P.ull[0]>>P.ull[1]>>buff;
    else if((flag=='P')||(flag=='p'))
      is>>buff>>P.ptr[0]>>P.ptr[1]>>P.ptr[2]>>P.ptr[3]>>buff;
    else is.SetState(FailBit);
    return is;
  }

  OutputBase& operator<<(OutputBase& os, const UniqueParameter128b& P) {
    os<<"L ["<<P.ull[0]<<"\t"<<P.ull[1]<<" ] ";
    return os;
  }

}

#endif
