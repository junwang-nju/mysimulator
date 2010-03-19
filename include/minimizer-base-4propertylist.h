
#ifndef _Minimizer_Base_For_Property_List_H_
#define _Minimizer_Base_For_Property_List_H_

#include "var-property-list.h"
#include "var-parameter-list.h"
#include "minimizer-base.h"

namespace std {

  template <typename DistEvalMethod, typename GeomType>
  class MinimizerKernelBase4PropertyList
    : public MinimizerKernelBase<refVector<double>,varParameterList> {

    public:

      typedef MinimizerKernelBase4PropertyList<DistEvalMethod,GeomType>
              Type;

      typedef MinimizerKernelBase<refVector<double>,varParameterList>
              ParentType;

      varPropertyList<unsigned int> iMaskSeq;

      varPropertyList<double> dMaskSeq;

      DistEvalMethod  MinDEval;

      GeomType  MinGeo;

      InteractionMethod

  };

}

#endif

