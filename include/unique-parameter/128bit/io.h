
#ifndef _Unique_Parameter_128bit_InputOutput_H_
#define _Unique_Parameter_128bit_InputOutput_H_

#include "unique-parameter/128bit/interface.h"
#include "unique-parameter/check-input-mode.h"

namespace mysimulator {

  InputBase& operator>>(InputBase& is, UniqueParameter128Bit& P) {
    assert(IsValid(is));
    char flag='\n';
    while(isspace(flag))  is>>flag;
    if(isdigit(flag)||(flag=='+')||(flag=='-')) {
      is.unget(flag);
      is>>P.ld;
    } else {
      bool vflag;
      UniqueParameterInputModeName im=_CheckInputMode(is);
      if(im==VectorMode)  vflag=true;
      else if(im==ValueMode)  vflag=false;
      else Error("Unknown Mode for UniqueParameter-128bit Input!");
      if((flag=='G')||(flag=='g'))    is>>P.ld;
      else if((flag=='D')||(flag=='d')) {
        if(vflag)   is>>P.d[0]>>P.d[1];
        else        is>>P.d[0];
      } else if((flag=='L')||(flag=='l')) {
        if(vflag)   is>>P.ull[0]>>P.ull[1];
        else        is>>P.ull[0];
      } else if((flag=='F')||(flag=='f')) {
        if(vflag) for(unsigned int i=0;i<4;++i) is>>P.f[i];
        else      is>>P.f[0];
      } else if((flag=='U')||(flag=='u')) {
        if(vflag) for(unsigned int i=0;i<4;++i) is>>P.u[i];
        else      is>>P.u[0];
      } else if((flag=='I')||(flag=='i')) {
        if(vflag) for(unsigned int i=0;i<4;++i) is>>P.i[i];
        else      is>>P.i[0];
      } else if((flag=='S')||(flag=='s')) {
        if(vflag) for(unsigned int i=0;i<8;++i) is>>P.s[i];
        else      is>>P.s[0];
      } else if((flag=='C')||(flag=='c')) {
        if(vflag) {
          for(unsigned int i=0;i<16;++i) {
            flag='\n';
            while(isspace(flag))    is>>flag;
            P.c[i]=flag;
          }
        } else    is>>P.c[0];
      } else if((flag=='P')||(flag=='p')) {
        if(vflag) for(unsigned int i=0;i<4;++i) is>>P.ptr[i];
        else      is>>P.ptr[0];
      } else is.SetState(FailBit);
      if(!IsFailed(is)) {
        if(vflag) {
          flag='\n';
          while(isspace(flag))  is>>flag;
          assert(flag==']');
        }
      }
    }
    return is;
  }

  OutputBase& operator<<(OutputBase& os, const UniqueParameter128Bit& P) {
    assert(IsValid(os));
    os<<"L [ "<<P.ull[0]<<"\t"<<P.ull[1]<<" ]";
    return os;
  }

}

#endif

