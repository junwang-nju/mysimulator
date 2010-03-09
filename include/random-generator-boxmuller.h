
#ifndef _Random_Generator_BoxMuller_H_
#define _Random_Generator_BoxMuller_H_

#include "ref-vector.h"
//#include <cstdlib>
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
        urng.SetWithSeed(seed);
        isSecond=true;
        od=0.;
      }

      void FillArray(double* Array, const unsigned int size) {
        for(uint i=0;i<size;++i)  Array[i]=GenRandNormal();
      }

      void FillArray(VectorBase<double>& v) { FillArray(v.data(),v.size()); }

      const double& GenRandNormal() {
        isSecond=!isSecond;
        if(isSecond)  od=Y*R2;
        else {
          do {
            X=urng.GenRand_Open0Open1();   X+=X;   X-=1.;
            Y=urng.GenRand_Open0Open1();   Y+=Y;   Y-=1.;
            R2=X*X+Y*Y;
          } while( (R2>1.)||(R2==0) );
          R2=sqrt(-2.0*log(R2)/R2);
          od=X*R2;
        }
        return od;
      }

      const double& Default(const double&) { return GenRandNormal(); }

      void saveStatus(ostream& os) {
        unsigned int op=os.precision();
        os.precision(20);
        urng.saveStatus(os);
        os<<"\t"<<X<<"\t"<<Y<<"\t"<<R2<<"\t"<<isSecond;
        os.precision(op);
      }

      void loadStatus(istream& is) {
        urng.loadStatus(is);
        is>>X>>Y>>R2>>isSecond;
      }

  };

  template <typename UniformDbRNGType>
  void BuildRationalVector(const BoxMuller<UniformDbRNGType>& rg,
                           const VectorBase<double>& iV,
                           refVector<double>& rV) {
    rV.refer(iV);
  }


}

#endif

