
#ifndef _Unique_Parameter_64bit_InputOutput_H_
#define _Unique_Parameter_64bit_InputOutput_H_

#include "unique-parameter/64bit/interface.h"
#include "unique-parameter/check-input-mode.h"

namespace mysimulator {

  InputBase& operator>>(InputBase& is, UniqueParameter64Bit& P) {
    assert(IsValid(is));
    char flag='\n';
    while(isspace(flag))  is>>flag;
    if(isdigit(flag)||(flag=='+')) {
      is.unget(flag);
      is>>P.ull;
    } else {
      bool vflag;
      UniqueParameterInputModeName im=_CheckInputMode(is);
      if(im==VectorMode)  vflag=true;
      else if(im==ValueMode)  vflag=false;
      else Error("Unknown Mode for UniqueParameter-64bit Input!");
      if((flag=='D')||(flag=='d'))        is>>P.d;
      else if((flag=='L')||(flag=='l'))   is>>P.ull;
      else if((flag=='F')||(flag=='f')) {
        if(vflag) is>>P.f[0]>>P.f[1];
        else      is>>P.f[0];
      } else if((flag=='U')||(flag=='u')) {
        if(vflag) is>>P.u[0]>>P.u[1];
        else      is>>P.u[0];
      } else if((flag=='I')||(flag=='i')) {
        if(vflag) is>>P.i[0]>>P.i[1];
        else      is>>P.i[0];
      } else if((flag=='S')||(flag=='s')) {
        if(vflag) for(unsigned int i=0;i<4;++i) is>>P.s[i];
        else      is>>P.s[0];
      } else if((flag=='C')||(flag=='c')) {
        if(vflag) {
          for(unsigned int i=0;i<8;++i) {
            flag='\n';
            while(isspace(flag)) is>>flag;
            P.c[i]=flag;
          }
        } else    is>>P.c[0];
      } else if((flag=='P')||(flag=='p')) {
        if(vflag) is>>P.ptr[0]>>P.ptr[1];
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

  OutputBase& operator<<(OutputBase& os, const UniqueParameter64Bit& P) {
    assert(IsValid(os));
    os<<P.ull;
    return os;
  }

}

#endif

