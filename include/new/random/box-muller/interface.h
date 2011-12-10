
#ifndef _Random_BoxMuller_Interface_H_
#define _Random_BoxMuller_Interface_H_

#include "random/base/interface.h"
#include "array/1d/interface.h"
#include <cmath>

namespace mysimulator {

  template <typename UniformRNG>
  struct BoxMuller : public RandomBase {

    public:

      typedef BoxMuller<UniformRNG>   Type;
      typedef RandomBase    ParentType;

      UniformRNG urng;
      Array1D<double> s;
      bool isSecond;

      BoxMuller() : ParentType(), urng(), s(), isSecond(true) {}
      ~BoxMuller() { clearData(); }

      void clearData() { release(urng); release(s); isSecond=true; }
      bool isvalid() const { return IsValid(urng)&&IsValid(s); }

      virtual void init(const unsigned int& seed) {
        urng.init(seed);
        isSecond=false;
      }
      virtual void init(const Array1DContent<unsigned int>& key) {
        urng.init(key);
        isSecond=false;
      }

      const double _drand() {
        doble d;
        if(isSecond) d=s[1]*s[2];
        else {
          do {
            s[0]=urng.randomDouble(); s[0]+=s[0]; s[0]-=1.;
            s[1]=urng.randomDouble(); s[1]+=s[1]; s[1]-=1.;
            s[2]=s[0]*s[0]+s[1]*s[1];
          } while((s[2]>1.)&&(s[2]==0.));
          s[2]=sqrt(-2.0*log(s[2])/s[2]);
          d=s[0]*s[2];
        }
        isSecond=!isSecond;
        return d;
      }

      virtual const double randomDouble() { return _drand(); }
      virtual const unsigned int randomUInt() {
        Error("Box-Muller Cannot generate Unsigned Int!");
        return uZero;
      }

    private:

      BoxMuller(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename UniformRNG>
  void release(BoxMuller<UniformRNG>& R) { R.clearData(); }

  template <typename UniformRNG>
  bool IsValid(const BoxMuller<UniformRNG>& R) { return R.isvalid(); }

}

#endif

