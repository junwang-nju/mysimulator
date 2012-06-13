
#ifndef _Random_BoxMuller_Interface_H_
#define _Random_BoxMuller_Interface_H_

#include "array/data/interface.h"
#include <cmath>

namespace mysimulator {

  template <typename UniformRNG>
  class BoxMuller {

    public:

      typedef BoxMuller<UniformRNG>   Type;
      template <typename UG> friend void Clear(BoxMuller<UG>&);

      BoxMuller() : urng(),rX(0),rY(0),rR(0),isSecond(false) {}
      ~BoxMuller() { Clear(*this); }

      bool IsValid() const { return urng.IsValid(); }
      void Allocate() { urng.Allocate(); isSecond=false; }
      void Init(unsigned int seed) { urng.Init(seed); isSecond=false; }
      void Init(const ArrayData<unsigned int>& A) {
        urng.Init(A); isSecond=false;
      }
      double Double() {
        double d;
        if(isSecond)  s=sY*sR;
        else {
          do {
            sX=urng.Double(); sX+=sX; sX-=1.;
            sY=urng.Double(); sY+=sY; sY-=1.;
            sR=sX*sX+sY*sY;
          } while((sR>1.)||(sR==0));
          sR=sqrt(-2.0*log(sR)/sR);
          d=sX*sR;
        }
        isSecond=!isSecond;
        return d;
      }
      unsigned int UInt() {
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
