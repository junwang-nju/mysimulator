
#ifndef _Interaction_for_ListSet_H_
#define _Interaction_for_ListSet_H_

#include "interaction-4list.h"

namespace std {

  template <typename DistEvalObj, typename GeomType, uint bMode>
  void E_ListSet(
    const VectorBase<refVector<double> >& Coordinate,
    VectorBase<InteractionList<DistEvalObj,GeomType,bMode> >& ILS,
    const ParamList& PList,DistEvalObj& DEval, const GeomType& Geo,
    double& Energy){
    uint n=ILS.size();
    for(uint i=0;i<n;++i) E_List(Coordinate,ILS[i],PList,DEval,Geo,Energy);
  }

  template <typename DistEvalObj, typename GeomType, uint bMode>
  void G_ListSet(
    const VectorBase<refVector<double> >& Coordinate,
    VectorBase<InteractionList<DistEvalObj,GeomType,bMode> >& ILS,
    const ParamList& PList,DistEvalObj& DEval, const GeomType& Geo,
    VectorBase<refVector<double> >& Gradient) {
    uint n=ILS.size();
    for(uint i=0;i<n;++i) G_List(Coordinate,ILS[i],PList,DEval,Geo,Gradient);
  }

  template <typename DistEvalObj, typename GeomType, uint bMode>
  void EG_ListSet(
    const VectorBase<refVector<double> >& Coordinate,
    VectorBase<InteractionList<DistEvalObj,GeomType,bMode> >& ILS,
    const ParamList& PList,DistEvalObj& DEval, const GeomType& Geo,
    double& Energy,
    VectorBase<refVector<double> >& Gradient) {
    uint n=ILS.size();
    for(uint i=0;i<n;++i)
      EG_List(Coordinate,ILS[i],PList,DEval,Geo,Energy,Gradient);
  }

}

#endif

