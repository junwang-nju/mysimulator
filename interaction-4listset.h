
#ifndef _Interaction_for_ListSet_H_
#define _Interaction_for_ListSet_H_

#include "interaction-4list.h"

namespace std {

  template <typename DistEvalObj, typename GeomType>
  void E_ListSet(const VectorBase<Property>& PropSet,
                 const ParamList& PList,
                 varVector<IDList<DistEvalObj,GeomType> >& IDLS,
                 DistEvalObj& DEval, const GeomType& Geo,
                 double& Energy){
    uint n=IDLS.size();
    for(uint i=0;i<n;++i) E_List(PropSet,PList,IDLS[i],DEval,Geo,Energy);
  }

  template <typename DistEvalObj, typename GeomType>
  void G_ListSet(VectorBase<Property>& PropSet,
                 const ParamList& PList,
                 varVector<IDList<DistEvalObj,GeomType> >& IDLS,
                 DistEvalObj& DEval, const GeomType& Geo) {
    uint n=IDLS.size();
    for(uint i=0;i<n;++i) G_List(PropSet,PList,IDLS[i],DEval,Geo);
  }

  template <typename DistEvalObj, typename GeomType>
  void EG_ListSet(VectorBase<Property>& PropSet,
                  const ParamList& PList,
                  varVector<IDList<DistEvalObj,GeomType> >& IDLS,
                  DistEvalObj& DEval, const GeomType& Geo,
                  double& Energy){
    uint n=IDLS.size();
    for(uint i=0;i<n;++i) EG_List(PropSet,PList,IDLS[i],DEval,Geo,Energy);
  }

}

#endif

