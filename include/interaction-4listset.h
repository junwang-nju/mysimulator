
#ifndef _Interaction_for_List_Set_H_
#define _Interaction_for_List_Set_H_

#include "interaction-4list.h"

namespace std {

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecTypeP,
            typename RunDistEvalMethod, typename RunGeomType>
  void EFunc(const VectorBase<refVector<double> >& CoorSeq,
             const VectorBase<InteractionMethod<DistEvalMethod,GeomType> >& IM,
             const VectorBase<refVector<refVector<unsigned int> > >& IdxLst,
             const VectorBase<unsigned int>& KindSeq,
             const ParameterListBase<VecTypeP>& ParamCollection,
             RunDistEvalMethod& DEval, RunGeomType& Geo, double& Energy) {
    assert(IM.size()==IdxLst.size());
    for(unsigned int i=0;i<IdxLst.size();++i)
      EFunc(CoorSeq,IM[i],IdxLst[i],KindSeq,ParamCollection,DEval,Geo,Energy);
  }

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            typename RunDistEvalMethod, typename RunGeomType>
  void EFunc(const VectorBase<refVector<double> >& CoorLst,
             const VectorBase<InteractionMethod<DistEvalMethod,GeomType> >& IM,
             const VectorBase<refVector<unsigned int> >& IdxLst,
             const VectorBase<refVector<double> >& ParamLst,
             RunDistEvalMethod& DEval, RunGeomType& Geo, double& Energy) {
    assert(CoorLst.size()==IM.size());
    assert(CoorLst.size()==IdxLst.size());
    assert(CoorLst.size()==ParamLst.size());
    for(unsigned int i=0;i<CoorLst.size();++i)
      EFunc(CoorLst[i],IM[i],IdxLst[i],ParamLst[i],DEval,Geo,Energy);
  }

}

#endif

