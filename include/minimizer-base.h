
#ifndef _Minimizer_Base_H_
#define _Minimizer_Base_H_

#include "var-vector.h"

namespace std {

  template <typename SpaceVecType, typename ParameterType>
  class MinimizerKernelBase {

    public:

      typedef MinimizerKernelBase<SpaceVecType,ParameterType> Type;

      typedef void (*EFuncType)(const SpaceVecType&,double&,
                                ParameterType&);

      typedef void (*GFuncType)(const SpaceVecType&,
                                VectorBase<SpaceVecType>&,ParameterType&);

      typedef void (*BFuncType)(const SpaceVecType&, double&,
                                VectorBase<SpaceVecType>&,ParameterType&);

      EFuncType MinEFunc;

      GFuncType MinGFunc;

      BFuncType MinBFunc;

      SpaceVecType MinCoorSeq;

      double MinE;

      SpaceVecType MinGradSeq;

      ParameterType MinParam;

      double MinPrj;

      double MinMove;

      unsigned int MinGCount;

      double MinScale;

      MinimizerKernelBase()
        : MinEFunc(NULL), MinGFunc(NULL), MinBFunc(NULL), MinCoorSeq(),
          MinE(0.), MinGradSeq(), MinParam(), MinPrj(0.), MinMove(0.),
          MinGCount(0), MinScale(0.1) {}

      MinimizerKernelBase(const Type& MKB) {
        myError("Cannot create from Minimizer Kernel Base");
      }

      Type& operator=(const Type& MKB) {
        MinEFunc=MKB.MinEFunc;
        MinGFunc=MKB.MinGFunc;
        MinBFunc=MKB.MinBFunc;
        MinCoorSeq=MKB.MinCoorSeq;
        MinE=MKB.MinE;
        MinGradSeq=MKB.MinGradSeq;
        MinParam=MKB.MinParam;
        MinPrj=MKB.MinPrj;
        MinMove=MKB.MinMove;
        MinGCount=MKB.MinGCount;
        MinScale=MKB.MinScale;
        return *this;
      }

      virtual ~MinimizerKernelBase() {}

      void clear() {
        MinEFunc=NULL;
        MinGFunc=NULL;
        MinBFunc=NULL;
        MinCoorSeq.clear();
        MinE=0.;
        MinGradSeq.clear();
        MinPrj=0.;
        MinMove=0.;
        MinGCount=0;
        MinScale=0.;
      }

  };

}

#endif

