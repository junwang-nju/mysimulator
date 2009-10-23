
#ifndef _Random_Generator_BoxMuller_H_
#define _Random_Generator_BoxMuller_H_

#include <cstdlib>
#include <cmath>
#include <cassert>

namespace std {

  template <typename UniformDbRNGType>
  class BoxMuller {

    private:

      double X,Y,R2;

      bool isSecond;

      double od;

    public:

      typedef BoxMuller<UniformDbRNGType> Type;

      UniformDbRNGType urng;

      BoxMuller() : isSecond(true), od(0.), urng() {}

      BoxMuller(const uint& seed) { Init(seed); }

      BoxMuller(const Type& BM) { assert(false); }

      void Init(const uint& seed) {
        urng.SetAsSeed(seed);
        isSecond=true;
        od=0.;
      }

      void FillArray(double* Array, const uint& size) {
        for(uint i=0;i<size;++i)  Array[i]=GenRandNormal();
      }

      template <typename vType>
      void FillArray(vType& v) {
        assert(v.IsVector);
        FillArray(v.data(),v.size());
      }

      const double& GenRandNormal() {
        isSecond=!isSecond;
        if(isSecond)  od=Y*R2;
        else {
          do {
            X=urng();   X+=X;   X-=1.;
            Y=urng();   Y+=Y;   Y-=1.;
            R2=X*X+Y*Y;
          } while( (R2>1.)||(R2==0) );
          od=X*R2;
        }
        return od;
      }

      const double& Default(const double&) { return GenRandNormal(); }

  };

}

#endif

