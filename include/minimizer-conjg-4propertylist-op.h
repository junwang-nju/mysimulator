
#ifndef _Minimizer_ConjugateGradient_for_PropertyList_Operate_H_
#define _Minimizer_ConjugateGradient_for_PropertyList_Operate_H_

#include "minimizer-conjg.h"
#include "property-list.h"
#include "interaction-method.h"

namespace std {

  template <typename DistEvalMethod, typename GeomType,
            template <typename,typename> class MParameterType,
            template <typename,typename> class LineMinMethod>
  void buildMinimizer(
      ConjugateGradientMinimizer<PropertyList<double>,
                                 MParameterType<DistEvalMethod,GeomType>,
                                 LineMinMethod>& CM,
      const PropertyList<double>& Coor,
      const PropertyList<unsigned int>& iMask,
      const PropertyList<double>& dMask,
      const DistEvalMethod& DEval, const GeomType& Geo,
      const typename
      MParameterType<DistEvalMethod,GeomType>::ParameterStorageType& ParamLst,
      const Vector<InteractionMethod<DistEvalMethod,GeomType> >& IMLst,
      const typename
      MParameterType<DistEvalMethod,GeomType>::IndexStorageType& IdxLst) {
    assert(IsAvailable(CM));
    typedef LineMinMethod<PropertyList<double>,
                          MParameterType<DistEvalMethod,GeomType> >  PType;
    buildMinimizer(static_cast<PType&>(CM),
                   Coor,iMask,dMask,DEval,Geo,ParamLst,IMLst,IdxLst);
    Vector<unsigned int> sz;
    allocate(sz,Coor.nunit);
    for(unsigned int i=0;i<sz.size;++i) sz[i]=Coor[i].size;
    allocate(*(CM.Dirc),sz);
    allocate(*(CM.OldMinGrad),sz);
  }

}

#endif

