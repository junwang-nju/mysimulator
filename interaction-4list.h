
#ifndef _Interaction_for_List_H_
#define _Interaction_for_List_H_

#include "property-list.h"
#include "interaction-list.h"

namespace std {

  template <typename DistEvalObj, typename GeomType>
  void E_List(IDList<DistEvalObj,GeomType>& IDL,const ParamList& PList,
              DistEvalObj& DEval, const GeomType& Geo, double& Energy){
    uint nl=IDL.List.size();
    for(uint i=0;i<nl;++i)
      IDL.efunc(IDL.Coordinate[i],IDL.List[i],IDL.KindIdx[i],
                PList,DEval,Geo,Energy);
  }

  template <typename DistEvalObj, typename GeomType>
  void G_List(IDList<DistEvalObj,GeomType>& IDL,const ParamList& PList,
              DistEvalObj& DEval, const GeomType& Geo) {
    uint nl=IDL.List.size();
    for(uint i=0;i<nl;++i)
      IDL.gfunc(IDL.Coordinate[i],IDL.List[i],IDL.KindIdx[i],
                PList,DEval,Geo,IDL.Gradient[i]);
  }

  template <typename DistEvalObj, typename GeomType>
  void EG_List(IDList<DistEvalObj,GeomType>& IDL,const ParamList& PList,
               DistEvalObj& DEval, const GeomType& Geo,double& Energy) {
    uint nl=IDL.List.size();
    for(uint i=0;i<nl;++i)
      IDL.bfunc(IDL.Coordinate[i],IDL.List[i],IDL.KindIdx[i],
                PList,DEval,Geo,Energy,IDL.Gradient[i]);
  }

}

#endif

