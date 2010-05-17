
#ifndef _Minimizer_Line_Tracking_for_PropertyList_Operate_H_
#define _Minimizer_Line_Tracking_for_PropertyList_Operate_H_

#include "minimizer-line-tracking.h"
#include "minimizer-line-base-4propertylist-op.h"

namespace std {

  template <typename DistEvalMethod, typename GeomType,
            template <typename,typename> class MParameterType>
  void buildMinimizer(
      TrackingLineMinimizer<PropertyList<double>,
                            MParameterType<DistEvalMethod,GeomType> >& TLM,
      const PropertyList<double>& Coor,
      const PropertyList<unsigned int>& iMask,
      const PropertyList<double>& dMask,
      const DistEvalMethod& DEval, const GeomType& Geo,
      const typename
      MParameterType<DistEvalMethod,GeomType>::ParameterStorageType& ParamLst,
      const Vector<InteractionMethod<DistEvalMethod,GeomType> >& IMLst,
      const typename
      MParameterType<DistEvalMethod,GeomType>::IndexStorageType& IdxLst) {
    assert(IsAvailable(TLM));
    typedef LineMinimizerBase<PropertyList<double>,
                              MParameterType<DistEvalMethod,GeomType> > PType;
    buildMinimizer(static_cast<PType&>(TLM),Coor,iMask,dMask,DEval,Geo,
                                            ParamLst,IMLst,IdxLst);
    Vector<unsigned int> sz;
    allocate(sz,Coor.nunit);
    for(unsigned int i=0;i<sz.size;++i) sz[i]=Coor[i].size;
    allocate(*(TLM.RunCoor),sz);
    allocate(*(TLM.RunGrad),sz);
  }

}

#endif

