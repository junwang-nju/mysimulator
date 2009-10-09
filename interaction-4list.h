
#ifndef _Interaction_for_List_H_
#define _Interaction_for_List_H_

#include "property.h"
#include "id-list.h"

namespace std {

  template <typename DistEvalObj, typename GeomType>
  void E_List(const varVector<Property>& PropSet,
              const ParamList& PList,
              IDList<DistEvalObj,GeomType>& IDL,
              DistEvalObj& DEval, const GeomType& Geo,
              double& Energy){
    uint nl=IDL.List.size();
    uint nid=IDL.runProperty.size();
    for(uint i=0;i<nl;++i) {
      for(uint k=0;k<nid;++k)
        IDL.runProperty[k]=const_cast<Property*>(&PropSet[IDL.List[i][k]]);
      IDL.efunc(IDL.runProperty,PList,DEval,Geo,Energy);
    }
  }

  template <typename DistEvalObj, typename GeomType>
  void G_List(varVector<Property>& PropSet,
              const ParamList& PList,
              IDList<DistEvalObj,GeomType>& IDL,
              DistEvalObj& DEval, const GeomType& Geo) {
    uint nl=IDL.List.size();
    uint nid=IDL.runProperty.size();
    for(uint i=0;i<nl;++i) {
      for(uint k=0;k<nid;++k) IDL.runProperty[k]=&PropSet[IDL.List[i][k]];
      IDL.gfunc(IDL.runProperty,PList,DEval,Geo);
    }
  }

  template <typename DistEvalObj, typename GeomType>
  void EG_List(varVector<Property>& PropSet,
               const ParamList& PList,
               IDList<DistEvalObj,GeomType>& IDL,
               DistEvalObj& DEval, const GeomType& Geo,
               double& Energy) {
    uint nl=IDL.List.size();
    uint nid=IDL.runProperty.size();
    for(uint i=0;i<nl;++i) {
      for(uint k=0;k<nid;++k) IDL.runProperty[k]=&PropSet[IDL.List[i][k]];
      IDL.bfunc(IDL.runProperty,PList,DEval,Geo,Energy);
    }
  }

}

#endif

