
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
                     varVector<IDList<DistEvalObj,GeomType> >&,
                     const varVector<varVector<double> >&,
                     DistEvalObj&, const GeomType&);

      void (*allocfunc)(varVector<varVector<double> >&,const uint&);

      void (*setstep)(varVector<varVector<double> >&,const double&);

      void (*setrelax)(varVector<varVector<double> >&,const double&);

      void (*sync)(const Property&,varVector<varVector<double> >&);

      varVector<varVector<double> > PropagatorParam;

      typedef PropagatorFormat<DistEvalObj,GeomType>  Type;

      PropagatorFormat() : mvfunc(NULL), PropagatorParam() {}

  };

}

#endif

