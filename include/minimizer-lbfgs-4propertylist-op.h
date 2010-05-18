
#ifndef _Minimizer_LBFGS_for_PropertyList_Operate_H_
#define _Minimizer_LBFGS_for_PropertyList_Operate_H_

#include "minimizer-lbfgs.h"
#include "property-list.h"
#include "interaction-method.h"

namespace std {

  template <typename DistEvalMethod, typename GeomType,
            template <typename,typename> class MParameterType,
            template <typename,typename> class LineMinMethod,
            unsigned int MaxCorr>
  void buildMinimizer(
      LBFGSMinimizer<PropertyList<double>,
                     MParameterType<DistEvalMethod,GeomType>,
                     LineMinMethod,MaxCorr>& LM,
      const PropertyList<double>& Coor,
      const PropertyList<unsigned int>& iMask,
      const PropertyList<double>& dMask,
      const DistEvalMethod& DEval, const GeomType& Geo,
      const typename
      MParameterType<DistEvalMethod,GeomType>::ParameterStorageType& ParamLst,
      const Vector<InteractionMethod<DistEvalMethod,GeomType> >& IMLst,
      const typename
      MParameterType<DistEvalMethod,GeomType>::IndexStorageType& IdxLst) {
    assert(IsAvailable(LM));
    typedef LineMinMethod<PropertyList<double>,
                          MParameterType<DistEvalMethod,GeomType> >  PType;
    buildMinimizer(static_cast<PType&>(LM),
                   Coor,iMask,dMask,DEval,Geo,ParamLst,IMLst,IdxLst);
    Vector<unsigned int> sz;
    allocate(sz,Coor.nunit);
    for(unsigned int i=0;i<sz.size;++i) sz[i]=Coor[i].size;
    allocate(*(LM.Dirc),sz);
    for(unsigned int i=0;i<MaxCorr;++i) {
      allocate(LM.dX[i],sz);
      allocate(LM.dG[i],sz);
    }
    allocate(*(LM.lastX),sz);
    allocate(*(LM.lastG),sz);
  }

}

#endif

