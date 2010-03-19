
#ifndef _Minimizer_Base_H_
#define _Minimizer_Base_H_

#include "ref-vector.h"

namespace std {

  template <typename SpaceVecType, typename ParameterType>
  class MinimizerKernelBase {

    public:

      typedef void (*EFuncType)(const VectorBase<SpaceVecType>&, double&);

      typedef void (*GFuncType)(const VectorBase<SpaceVecType>&,
                                VectorBase<SpaceVecType>&);

      typedef void (*BFuncType)(const VectorBase<SpaceVecType>&, double&,
                                VectorBase<SpaceVecType>&);

      EFuncType MinEFunc;

      GFuncType MinGFunc;

      BFuncType MinBFunc;

      refVector<SpaceVecType> MinCoorSeq;

      double MinE;

      refVector<SpaceVecType> MinGradSeq;

      ParameterType MinParam;

      double MinPrj;

      double MinMove;

      unsigned int MinGCount;

      double MinScale;

      MinimizerKernelBase()
        : MinEFunc(NULL), MinGFunc(NULL), MinBFunc(NULL), MinCoorSeq(),
          MinE(0.), MinGradSeq(), MinParam(), MinPrj(0.), MinMove(0.),
          MinGCount(0), MinScale(0.1) {}

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

      virtual void ImportState(const VectorBase<SpaceVecType>&,
                               const ParameterType&) = 0;

  };

}

#endif

