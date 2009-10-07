
#ifndef _ID_List_H_
#define _ID_List_H_

#include "property.h"
#include "param-list.h"

namespace std {

  template <typename DistEvalObj, typename GeomType>
  class IDList {

    public:

      void (*efunc)(const varVector<Property*>&, const ParamList&,
                    DistEvalObj&, const GeomType&,double&);

      void (*gfunc)(const varVector<Property*>&, const ParamList&,
                    DistEvalObj&, const GeomType&);

      void (*bfunc)(const varVector<Property*>&, const ParamList&,
                    DistEvalObj&, const GeomType&, double&);

      varVector<varVector<uint> > List;
      
      varVector<Property*> runProperty;

      typedef IDList<DistEvalObj,GeomType>    Type;

      IDList()
        : efunc(NULL), gfunc(NULL), bfunc(NULL), List(), runProperty() {
      }

      IDList(const Type& IDL) { myError("copier for IDList is disabled!"); }

      Type& operator=(const Type& IDL) {
        List=IDL.List;
        return *this;
      }

      template <typename runDistEvalObj, typename runGeomType>
      Type& operator=(const IDList<runDistEvalObj,runGeomType>& IDL) {
        List=IDL.List;
        return *this;
      }

      Type& allocate(const uint& NL, const uint& NID) {
        List.allocate(NL);
        for(uint i=0;i<NL;++i)  List[i].allocate(NID);
        runProperty.allocate(NID);
        return *this;
      }

      template <typename runDistEvalObj, typename runGeomType>
      Type& allocate(const IDList<runDistEvalObj,runGeomType>& IDL) {
        uint nl=IDL.List.size();
        uint nid=IDL.List[0].size();
        return allocate(nl,nid);
      }

  };

}

#endif

