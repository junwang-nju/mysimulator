
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
      typedef RandomBase  ParentType;

      UniformRNG urng;
      Array1D<double> s;
      bool isSecond;

      BoxMuller() : ParentType(), urng(), s(), isSecond(true) {}
      ~BoxMuller() { Clear(*this); }

      bool IsValid() const { return urng.IsValid()&&s.IsValid(); }

      void Allocate() {
        Clear(*this);
        urng.Allocate();
        s.Allocate(3);
        isSecond=false;
      }

      virtual void Init(unsigned int seed) {
        urng.Init(seed);
        isSecond=false;
      }

      void Init(const Array1D<unsigned int>& key,unsigned int n) {
        urng.Init(key,n);
        isSecond=false;
      }

      virtual double Double() {
        double d;
        if(isSecond)  d=s[1]*s[2];
        else {
          do {
            s[0]=urng.Double(); s[0]+=s[0]; s[0]-=1.;
            s[1]=urng.Double(); s[1]+=s[1]; s[1]-=1.;
            s[2]=s[0]*s[0]+s[1]*s[1];
          } while((s[2]>1.)||(s[2]==0));
          s[2]=sqrt(-2.0*log(s[2])/s[2]);
          d=s[0]*s[2];
        }
        isSecond=!isSecond;
        return d;
      }

      virtual unsigned int UInt() {
        fprintf(stderr,"Box-Muller DO NOT Generate Unsigned Int!\n");
        return 0;
      }

    private:

      BoxMuller(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename UR>
  void Clear(BoxMuller<UR>& R) { Clear(R.urng); Clear(R.s); R.isSecond=true; }

}

#endif

