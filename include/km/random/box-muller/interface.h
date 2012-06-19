
#ifndef _Random_BoxMuller_Interface_H_
#define _Random_BoxMuller_Interface_H_

#include "random/interface.h"
#include <cmath>

namespace mysimulator {

  template <typename UniformRNG>
  class BoxMuller : public Random {

    public:

      typedef BoxMuller<UniformRNG>   Type;
      typedef Random  ParentType;
      template <typename UG> friend void Clear(BoxMuller<UG>&);

      BoxMuller() : urng(),rX(0),rY(0),rR(0),isSecond(false) {}
      virtual ~BoxMuller() { Clear(*this); }

      virtual bool IsValid() const { return urng.IsValid(); }
      virtual void Allocate() { urng.Allocate(); isSecond=false; }
      virtual void Init(unsigned int seed) { urng.Init(seed); isSecond=false; }
      virtual void Init(const ArrayData<unsigned int>& A) {
        urng.Init(A); isSecond=false;
      }
      virtual double Double() {
        double d;
        if(isSecond)  d=rY*rR;
        else {
          do {
            rX=urng.Double(); rX+=rX; rX-=1.;
            rY=urng.Double(); rY+=rY; rY-=1.;
            rR=rX*rX+rY*rY;
          } while((rR>1.)||(rR==0));
          rR=sqrt(-2.0*log(rR)/rR);
          d=rX*rR;
        }
        isSecond=!isSecond;
        return d;
      }
      virtual unsigned int UInt() {
        fprintf(stderr,"Box-Muller Does Not Produce Unsigned Int!");
        return 0;
      }

    protected:

      UniformRNG urng;
      double rX,rY,rR;
      bool isSecond;

    private:

      BoxMuller(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename UG>
  void Clear(BoxMuller<UG>& R) { Clear(R.urng); R.isSecond=false; }

}

#endif

