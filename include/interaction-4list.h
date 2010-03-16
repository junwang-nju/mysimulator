
#ifndef _Interaction_for_List_H_
#define _Interaction_for_List_H_

#include "property-list-base.h"
#include "parameter-list-base.h"
#include "interaction-method.h"
#include "var-vector.h"

namespace std {

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecTypeD,
            template <typename> class VecTypeG>
  void EFunc(const VectorBase<refVector<double> >& Coor,
             const InteractionMethod<DistEvalMethod,GeomType>& IM,
             const VectorBase<refVector<unsigned int> >& IdxLst,
             const VectorBase<refVector<double> >& ParamLst,
             DistEvalMethod<VecTypeD>& DEval, const GeomType<VecTypeG>& Geo,
             double& Energy) {
    unsigned int n=IdxLst.size();
    if(n==0)  return;
    varVector<refVector<double> > rCoor(IdxLst[0].size());
    for(unsigned int i=0;i<n;++i) {
    }
  }

}

#endif
