
#ifndef _Monomer_Propagator_Format_H_
#define _Monomer_Propagator_Format_H_

#include "property.h"
#include "interaction-4listset.h"

namespace std {

  template <typename DistEvalObj, typename GeomType>
  class MonomerPropagatorFormat {

    public:

      typedef void (* MyFuncType)(Property&,
                                  const varVector<varVector<double> >&);

      typedef void (* SetFuncType)(varVector<varVector<double> >&,
                                   const double*, const uint&);

      varVector<MyFuncType> mvfunc;

      varVector<SetFuncType>  setfunc;

      void (*alloc)(varVector<varVector<double> >&,const uint*,const uint&);

      void (*sync)(const Property&,varVector<varVector<double> >&);

      varVector<varVector<double> > PropagatorParam;

      typedef MonomerPropagatorFormat<DistEvalObj,GeomType>  Type;

      MonomerPropagatorFormat() : PropagatorParam() {}

  };

}

#endif

