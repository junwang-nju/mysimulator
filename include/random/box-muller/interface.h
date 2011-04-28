
#ifndef _Random_Box_Muller_Interface_H_
#define _Random_Box_Muller_Interface_H_

#include "random/base/interface.h"

namespace mysimulator {

  template <typename UniformRNG>
  struct BoxMuller : public RandomBase {

    typedef BoxMuller<UniformRNG>   Type;
    typedef RandomBase    ParentType;

    UniformRNG urng;
    double s[3];
    bool isSecond;

    BoxMuller() : urng(), isSecond(true) {}
    BoxMuller(const Type&) { Error("Copier of BoxMuller Disabled!"); }
    Type& operator=(const Type&) {
      Error("Operator= for BoxMuller Disabled!");
      return *this;
    }
    ~BoxMuller() { clearData(); }

    void clearData() { urng.clearData(); isSecond=true; }
    virtual void init(const unsigned int seed) {
      init(urng,seed);
      isSecond=false;
    }
    const double _drand() {
      double d;
      if(isSecond)  d=s[1]*s[2];
      else {
        do{
          s[0]=urng.randomDouble(); s[0]+=s[0];   s[0]-=1.;
          s[1]=urng.randomDouble(); s[1]+=s[1];   s[1]-=1.;
          s[2]=s[0]*s[0]+s[1]*s[1];
        }while((s[2]>1.)||(s[2]==0));
        s[2]=sqrt(-2.0*log(s[2])/s[2]);
        d=s[0]*s[2];
      }
      isSecond=!isSecond;
      return d;
    }
    virtual const double randomDouble() { return _drand(); }
    virtual const unsigned int randomUnsignedInt() {
      Error("Unsigned-Int Output Disabled for Box-Muller!");
      return uZero;
    }

  };

  template <typename UniformRNG>
  bool IsValid(const BoxMuller<UniformRNG>& G) { return IsValid(G.urng); }

  template <typename UniformRNG>
  void release(BoxMuller<UniformRNG>& G) { G.clearData(); }

}

#endif

