
#ifndef _Interaction_for_ListSet_H_
#define _Interaction_for_ListSet_H_

#include "interaction-4list.h"

namespace std {

  template <typename DistEvalObj, typename GeomType>
  void E_ListSet(VectorBase<IDList<DistEvalObj,GeomType> >& IDLS,
                 const ParamList& PList,
                 DistEvalObj& DEval, const GeomType& Geo,
                 double& Energy){
    uint n=IDLS.size();
    for(uint i=0;i<n;++i) E_List(IDLS[i],PList,DEval,Geo,Energy);
  }

  template <typename DistEvalObj, typename GeomType>
  void G_ListSet(VectorBase<IDList<DistEvalObj,GeomType> >& IDLS,
                 const ParamList& PList,
                 DistEvalObj& DEval, const GeomType& Geo) {
    uint n=IDLS.size();
    for(uint i=0;i<n;++i) G_List(IDLS[i],PList,DEval,Geo);
  }

  template <typename DistEvalObj, typename GeomType>
  void EG_ListSet(VectorBase<IDList<DistEvalObj,GeomType> >& IDLS,
                  const ParamList& PList,
                  DistEvalObj& DEval, const GeomType& Geo,
                  double& Energy){
    uint n=IDLS.size();
    for(uint i=0;i<n;++i) EG_List(IDLS[i],PList,DEval,Geo,Energy);
  }

}

#endif

