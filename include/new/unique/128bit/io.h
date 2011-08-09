
#ifndef _Unique_128Bit_InputOutput_H_
#define _Unique_128Bit_InputOutput_H_

#include "unique/128bit/interface.h"
#include "unique/check-input-mode.h"

namespace mysimulator {

  InputBase& operator>>(InputBase& is, Unique128Bit& U) {
    assert(IsValid(is));
    char flag='\n';
    while(isspace(flag))  is>>flag;
    if(isdigit(flag)||(flag=='+')||(flag=='-')) {
      is.unget(flag);
      is>>U.ld;
    } else {
      bool vflag;
      vflag=(_InputMode(is)==VectorMode?true:false);
      if((flag=='G')||(flag=='g'))  is>>U.ld;
      else if((flag=='D')||(flag=='d')) { is>>U.d[0]; if(vflag) is>>U.d[1]; }
      else if((flag=='L')||(flag=='l')) {
        is>>U.ull[0]; if(vflag) is>>U.ull[1];
      } else if((flag=='F')||(flag=='f')) {
        is>>U.f[0]; if(vflag) is>>U.f[1]>>U.f[2]>>U.f[3];
      } else if((flag=='U')||(flag=='u')) {
        is>>U.u[0]; if(vflag) for(unsigned int i=1;i<4;++i) is>>U.u[i];
      } else if((flag=='I')||(flag=='i')) {
        is>>U.i[0]; if(vflag) for(unsigned int i=1;i<4;++i) is>>U.i[i];
      } else if((flag=='S')||(flag=='s')) {
        is>>U.s[0]; if(vflag) for(unsigned int i=1;i<8;++i) is>>U.s[i];
      } else if((flag=='C')||(flag=='c')) {
        if(vflag) {
          for(unsigned int i=0;i<16;++i) {
            flag='\n';
            while(isspace(flag))  is>>flag;
            U.c[i]=flag;
          }
        } else is>>U.c[0];
      } else if((flag=='P')||(flag=='p')) {
        is>>U.ptr[0]; if(vflag) for(unsigned int i=1;i<4;++i) is>>U.ptr[i];
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

  OutputBase& operator<<(OutputBase& os, const Unique128Bit& U) {
    assert(IsValid(os));
    os<<"L [ "<<U.ull[0]<<"\t"<<U.ull[1]<<" ]";
    return os;
  }

}

#endif

