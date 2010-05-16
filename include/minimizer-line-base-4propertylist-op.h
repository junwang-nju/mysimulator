
#ifndef _Minimizer_Line_Base_for_PropertyList_Operate_H_
#define _Minimizer_Line_Base_for_PropertyList_Operate_H_

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
    const typename
    MParameterType<DistEvalMethod,GeomType>::IndexStorageType& IdxLst) {
    allocate(LM);
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
    refer(LM.MinParam->ParamLst,ParamLst);
    refer(LM.MinParam->IMLst,IMLst);
    refer(LM.MinParam->IdxLst,IdxLst);
    finalize(*(LM.MinParam));
    updateParameter(*(LM.MinParam));
    *(LM.MinEnergy)=0.;
    assign(*(LM.MinGrad),0.);
    LM.MinBFunc(*(LM.MinCoor),*(LM.MinEnergy),*(LM.MinGrad),*(LM.MinParam));
  }

  template <typename DistEvalMethod, typename GeomType,
            template <typename,typename> class MParameterType>
  double minimalstep(
    LineMinimizerBase<PropertyList<double>,
                      MParameterType<DistEvalMethod,GeomType> >& LM,
    const PropertyList<double>& Origin,
    const PropertyList<double>& Dirc) {
    assert(Origin.nunit==Dirc.nunit);
    assert(Origin.nunit==LM.MinParam->nunit);
    double mstep=0., tmd;
    for(unsigned int i=0;i<Origin.nunit;++i)
    for(unsigned int j=0;j<Origin[i].size;++j) {
      if(LM.MinParam->iMask[i][j]==0) continue;
      tmd=fabs(Origin[i][j]);
      tmd=(tmd<1.?Dirc[i][j]:Dirc[i][j]/tmd);
      mstep+=tmd*tmd;
    }
    mstep=LM.MinParam->DOF/mstep;
    return DRelDelta*sqrt(mstep);
  }

}

#endif

