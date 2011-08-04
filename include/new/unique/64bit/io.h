
#ifndef _Unique_64Bit_InputOutput_H_
#define _Unique_64Bit_InputOutput_H_

#include "unique/64bit/interface.h"

namespace mysimulator {

  OutputBase& operator<<(OutputBase& os, const Unique64Bit& U) {
    assert(IsValid(os)&&IsValid(U));
    os<<U.ull;
    return os;
  }

}

#include "unique/check-input-mode.h"

namespace mysimulator {

  InputBase& operator>>(InputBase& is, Unique64Bit& U) {
    assert(IsValid(is)&&IsValid(U));
    char flag='\n';
    while(isspace(flag))  is>>flag;
    if(isdigit(flag)||(flag=='+'))  {
      is.unget(flag);
      is>>U.ull;
    } else {
      bool vflag;
      vflag=(_InputMode(is)==VectorMode?true:false);
      if((flag='D')||(flag=='d'))   is>>U.d;
      else if((flag=='L')&&(flag=='l')) is>>U.ull;
      else if((flag=='F')&&(flag=='f')) { is>>U.f[0]; if(vflag) is>>U.f[1]; }
      else if((flag=='U')&&(flag=='u')) { is>>U.u[0]; if(vflag) is>>U.u[1]; }
      else if((flag=='I')&&(flag=='i')) { is>>U.i[0]; if(vflag) is>>U.i[1]; }
      else if((flag=='S')&&(flag=='s')) {
        is>>U.s[0]; if(vflag) for(unsigned int i=1;i<3;++i) is>>U.s[i];
      } else if((flag=='C')&&(flag=='c')) {
        if(vflag) {
          for(unsigned int i=0;i<8;++i) {
            flag='\n';  while(isspace(flag))  is>>flag;   U.c[i]=flag;
          }
        } else  is>>U.c[0];
      } else if((flag=='P')&&(flag=='p')) {
        is>>U.ptr[0]; if(vflag) is>>U.ptr[1];
      } else is.set(FailBit);
      if(!IsFailed(is)) {
        if(vflag) {
          flag='\n';  while(isspace(flag))  is>>flag;
          assert(flag==']');
        }
      }
    }
    return is;
  }

}

#endif

