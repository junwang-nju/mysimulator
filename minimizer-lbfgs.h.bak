
#ifndef _Minimizer_LBFGS_H_
#define _Minimizer_LBFGS_H_

#include "minimizer-base.h"

namespace std {

  template <typename DistEvalObj, typename GeomType,uint MaxCorr=6,
            template <typename, typename> class MinKern=CoarseMinimizerKern>
  class LBFGSMin : public MinKern<DistEvalObj,GeomType> {

    public:

      typedef LBFGSMin<DistEvalObj,GeomType,MaxCorr,MinKern>  Type;

      typedef MinKern<DistEvalObj,GeomType>                   ParentType;

      static const uint DefaultMaxIter;

      LBFGSMin() { myError("Not Implementated!"); }

  };

  template <typename DistEvalObj, typename GeomType,uint MaxCorr,
            template <typename, typename> class MinKern>
  const uint LBFGSMin<DistEvalObj,GeomType,MaxCorr,MinKern>::DefaultMaxIter
      =1000;

}

#endif

