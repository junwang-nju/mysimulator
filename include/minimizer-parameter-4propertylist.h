
#ifndef _Minimizer_Parameter_For_PropertyList_H_
#define _Minimizer_Parameter_For_PropertyList_H_

#include "ref-property-list.h"
#include "parameter-list.h"
#include "interaction-method.h"

namespace std {

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType>
  class MinimizerParameter4PropertyList {

    public:

      typedef MinimizerParameter4PropertyList<DistEvalMethod,GeomType>  Type;

      refPropertyList<unsigned int>::Type iMaskSeq;

      refPropertyList<double>::Type dMaskSeq;

      DistEvalMethod<refVector> DEval;

      GeomType<refVector> Geo;

      refVector<refVector<double> >  ParamLst;

      refVector<InteractionMethod<DistEvalMethod,GeomType> > IMethodLst;

      refPropertyList<unsigned int>::Type IdxLst;

      refPropertyList<refVector<double> >::Type CoorLst;

      refPropertyList<refVector<double> >::Type GradLst;

      void update() { DEval.update(); }

  };

}

#endif

