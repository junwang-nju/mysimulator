
#ifndef _Unique_128Bit_Fill_H_
#define _Unique_128Bit_Fill_H_

#include "unique/128bit/interface.h"

namespace mysimulator {

  void Fill(Unique128Bit& U,const long double& ld) { U.ld=ld; }
  void Fill(Unique128Bit& U,const double& d1,const double& d2) {
    U.dv[0]=d1; U.dv[1]=d2;
  }
  void Fill(Unique128Bit& U,const double& d) { Fill(U,d,d); }
  void Fill(Unique128Bit& U,const long long& ll1,const long long& ll2) {
    U.llv[0]=ll1; U.llv[1]=ll2;
  }
  void Fill(Unique128Bit& U,const long long& ll) { Fill(U,ll,ll); }
  void Fill(Unique128Bit& U,
            const unsigned long long& ull1,const unsigned long long& ull2) {
    U.ullv[0]=ull1; U.ullv[1]=ull2;
  }
  void Fill(Unique128Bit& U,const unsigned long long& ull) { Fill(U,ull,ull); }
  void Fill(Unique128Bit& U,
            const float& f1,const float& f2,const float& f3,const float& f4) {
    U.fv[0]=f1; U.fv[1]=f2; U.fv[2]=f3; U.fv[3]=f4;
  }
  void Fill(Unique128Bit& U,const float& f) { Fill(U,f,f,f,f); }
  void Fill(Unique128Bit& U,int i1,int i2,int i3,int i4) {
    U.iv[0]=i1; U.iv[1]=i2; U.iv[2]=i3; U.iv[3]=i4;
  }
  void Fill(Unique128Bit& U,int i) { Fill(U,i,i,i,i); }
  void Fill(Unique128Bit& U,
            unsigned int u1,unsigned int u2,unsigned int u3,unsigned int u4) {
    U.uv[0]=u1; U.uv[1]=u2; U.uv[2]=u3; U.uv[3]=u4;
  }
  void Fill(Unique128Bit& U,unsigned int u) { Fill(U,u,u,u,u); }
  void Fill(Unique128Bit& U,long l1,long l2,long l3,long l4) {
    U.lv[0]=l1; U.lv[1]=l2; U.lv[2]=l3; U.lv[3]=l4;
  }
  void Fill(Unique128Bit& U,long l) { Fill(U,l,l,l,l); }
  void Fill(Unique128Bit& U,unsigned long ul1,unsigned long ul2,
                            unsigned long ul3,unsigned long ul4) {
    U.ulv[0]=ul1; U.ulv[1]=ul2; U.ulv[2]=ul3; U.ulv[3]=ul4;
  }
  void Fill(Unique128Bit& U,unsigned long ul) { Fill(U,ul,ul,ul,ul); }
  void Fill(Unique128Bit& U,short s1,short s2,short s3,short s4,
                            short s5,short s6,short s7,short s8) {
    U.sv[0]=s1; U.sv[1]=s2; U.sv[2]=s3; U.sv[3]=s4; U.sv[4]=s5;
    U.sv[5]=s6; U.sv[6]=s7; U.sv[7]=s8;
  }
  void Fill(Unique128Bit& U,short s) { Fill(U,s,s,s,s,s,s,s,s); }
  void Fill(Unique128Bit& U,unsigned short us1,unsigned short us2,
            unsigned short us3,unsigned short us4,unsigned short us5,
            unsigned short us6,unsigned short us7,unsigned short us8) {
    U.usv[0]=us1; U.usv[1]=us2; U.usv[2]=us3; U.usv[3]=us4; U.usv[4]=us5;
    U.usv[5]=us6; U.usv[6]=us7; U.usv[7]=us8;
  }
  void Fill(Unique128Bit& U,unsigned short us) {
    Fill(U,us,us,us,us,us,us,us,us);
  }

}

#endif

