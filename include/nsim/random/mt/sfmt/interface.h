
#ifndef _Random_MT_SFMT_Interface_H_
#define _Random_MT_SFMT_Interface_H_

#include "random/mt/interface.h"
#include "random/base/interface.h"
#include "random/mt/sfmt/module/init-func.h"
#include "unique/128bit/fill.h"

namespace mysimulator {

  template <unsigned int Fac>
  struct MersenneTwister<SFMT,Fac> : public RandomBase {

    public:

      typedef MersenneTwister<SFMT,Fac>   Type;
      typedef RandomBase  ParentType;

      static const unsigned int N;
      static const unsigned int NByte;
      static const unsigned int N32;
      static const unsigned int N32m1;
      static const unsigned int N64;
      static const unsigned int Lag;
      static const unsigned int Mid;
      static const unsigned int LagMid;
      static const unsigned int Pos;
      static const unsigned int NmPos;
      static const unsigned int SL1;
      static const unsigned int SL2;
      static const unsigned int SR1;
      static const unsigned int SR2;
      static const Unique128Bit Msk;
      static const Unique128Bit Pty;

      Array1D<Unique128Bit> s;
      unsigned int idx;
      Unique128Bit _u;

      MersenneTwister() : ParentType(), s(), idx(0), _u() {}
      ~MersenneTwister() { Clear(*this); }

      bool IsValid() const { return s.IsValid(); }

      void _PeriodCertification() {
        unsigned int inner=0;
        unsigned int *p=reinterpret_cast<unsigned int*>(s._data);
        inner^=p[0]&Pty.uv[0];
        inner^=p[1]&Pty.uv[1];
        inner^=p[2]&Pty.uv[2];
        inner^=p[3]&Pty.uv[3];
        for(unsigned int i=16;i>0;i>>=1)  inner^=inner>>i;
        inner&=1;
        if(inner==1)  return;
      }

    private:

      MersenneTwister(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <unsigned int Fac>
  void Clear(MersenneTwister<SFMT,Fac>& R) {
    Clear(R.s); R.idx=0; Fill(R._u,0);
  }

}

#endif

