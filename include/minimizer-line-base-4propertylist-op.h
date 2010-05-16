
#ifndef _Minimizer_Line_Base_for_PropertyList_H_
#define _Minimizer_Line_Base_for_PropertyList_H_

#include "minimizer-line-base.h"
#include "minimizer-func-4propertylist.h"

namespace std {

  template <typename DistEvalMethod, typename GeomType,
            template <typename,typename> class MParameterType>
  void buildMinimizer(
    LineMinimizerBase<PropertyList<double>,
                      MParameterType<DistEvalMethod,GeomType> >& LM,
    const PropertyList<double>& Coor,
    const PropertyList<unsigned int>& iMask,
    const PropertyList<double>& dMask,
    const DistEvalMethod& DEval, const GeomType& Geo,
    const typename
    MParameterType<DistEvalMethod,GeomType>::ParameterStorageType& ParamLst,
    const Vector<InteractionMethod<DistEvalMethod,GeomType> >& IMLst,
    const PropertyList<unsigned int>& IdxLst) {
    assert(IsAvailable(LM));
    LM.MinEFunc=EFunc4PropertyList<DistEvalMethod,GeomType,MParameterType>;
    LM.MinGFunc=GFunc4PropertyList<DistEvalMethod,GeomType,MParameterType>;
    LM.MinBFunc=BFunc4PropertyList<DistEvalMethod,GeomType,MParameterType>;
    Vector<unsigned int> sz;
    allocate(sz,Coor.nunit);
    for(unsigned int i=0;i<sz.size;++i) sz[i]=Coor[i].size;
    allocate(*(LM.MinCoor),sz);
    allocate(*(LM.MinGrad),sz);
    assign(*(LM.MinCoor),Coor);
    refer(LM.MinParam->iMask,iMask);
    refer(LM.MinParam->dMask,dMask);
    refer(LM.MinParam->DEval,DEval);
    refer(LM.MinParam->Geo,Geo);
  }

}

#endif

