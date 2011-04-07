
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
        else        is>>P.dvalue;
      } else if((flag=='L')||(flag=='l')) {
        if(vflag)   is>>P.ull[0]>>P.ull[1];
        else        is>>P.ullvalue;
      } else if((flag=='F')||(flag=='f')) {
        if(vflag) for(unsigned int i=0;i<4;++i) is>>P.f[i];
        else      is>>P.fvalue;
      } else if((flag=='U')||(flag=='u')) {
        if(vflag) for(unsigned int i=0;i<4;++i) is>>P.u[i];
        else      is>>P.uvalue;
      } else if((flag=='I')||(flag=='i')) {
        if(vflag) for(unsigned int i=0;i<4;++i) is>>P.i[i];
        else      is>>P.ivalue;
      } else if((flag=='S')||(flag=='s')) {
        if(vflag) for(unsigned int i=0;i<8;++i) is>>P.s[i];
        else      is>>P.svalue;
      } else if((flag=='C')||(flag=='c')) {
        if(vflag) {
          for(unsigned int i=0;i<16;++i) {
            flag='\n';
            while(isspace(flag))    is>>flag;
            P.c[i]=flag;
          }
        } else    is>>P.cvalue;
      } else if((flag=='P')||(flag=='p')) {
        if(vflag) for(unsigned int i=0;i<4;++i) is>>P.ptr[i];
        else      is>>P.pvalue;
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
    assert(IsValid(ios));
    os<<"L [ "<<P.ull[0]<<"\t"<<P.ull[1]<<" ]";
    return os;
  }

}

#endif

