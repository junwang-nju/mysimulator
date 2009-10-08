
#ifndef _Propagator_Format_H_
#define _Propagator_Format_H_

#include "property.h"
#include "interaction-4listset.h"

namespace std {

  template <typename DistEvalObj, typename GeomType>
  class PropagatorFormat {

    public:

      void (*mvfunc)(Property&,
                     varVector<Property>&,const ParamList&,
                     IDListSet<DistEvalObj,GeomType>&,
                     const varVector<varVector<double> >&,
                     DistEvalObj&, const GeomType&);

      varVector<varVector<double> > PropagatorParam;

      typedef PropagatorFormat<DistEvalObj,GeomType>  Type;

      PropagatorFormat() : mvfunc(NULL), PropagatorParam() {}

  };

}

#endif

