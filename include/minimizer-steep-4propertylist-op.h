
#ifndef _Minimizer_SteepestDescent_for_PropertyList_Operate_H_
#define _Minimizer_SteepestDescent_for_PropertyList_Operate_H_

#include "minimizer-steep.h"
#include "property-list.h"
#include "interaction-method.h"

namespace std {

  template <typename DistEvalMethod, typename GeomType,
            template <typename,typename> class MParameterType,
            template <typename,typename> class LineMinMethod>
  void buildMinimizer(
      SteepestDescentMinimizer<PropertyList<double>,
                               MParameterType<DistEvalMethod,GeomType>,
                               LineMinMethod>& SM,
      const PropertyList<double>& Coor,
      const PropertyList<unsigned int>& iMask,
      const PropertyList<double>& dMask,
      const DistEvalMethod& DEval, const GeomType& Geo,
      const typename
      MParameterType<DistEvalMethod,GeomType>::ParameterStorageType& ParamLst,
      const Vector<InteractionMethod<DistEvalMethod,GeomType> >& IMLst,
      const typename
      MParameterType<DistEvalMethod,GeomType>::IndexStorageType& IdxLst) {
    assert(IsAvailable(SM));
    typedef LineMinMethod<PropertyList<double>,
                          MParameterType<DistEvalMethod,GeomType> >   PType;
    buildMinimizer(static_cast<PType&>(SM),
                   Coor,iMask,dMask,DEval,Geo,ParamLst,IMLst,IdxLst);
    Vector<unsigned int> sz;
    allocate(sz,Coor.nunit);
    for(unsigned int i=0;i<sz.size;++i) sz[i]=Coor[i].size;
    allocate(*(SM.Dirc),sz);
  }

}

#endif
