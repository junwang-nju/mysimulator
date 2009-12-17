
#ifndef _ID_List_H_
#define _ID_List_H_

#include "property.h"
#include "param-list.h"

namespace std {

  template <typename DistEvalObj, typename GeomType>
  class IDList {

    public:

      uint interactionTag;

      void (*efunc)(const VectorBase<PropertyComponent<refVector>*>&,
                    const ParamList&,DistEvalObj&,const GeomType&,
                    double&);

      void (*gfunc)(const VectorBase<PropertyComponent<refVector>*>&,
                    const ParamList&,DistEvalObj&,const GeomType&,
                    VectorBase<PropertyComponent<refVector>*>&);

      void (*bfunc)(const VectorBase<PropertyComponent<refVector>*>&,
                    const ParamList&,DistEvalObj&,const GeomType&,
                    double&,VectorBase<PropertyComponent<refVector>*>&);

      varVector<varVector<uint> > List;
      
      varVector<PropertyComponent<refVector>*>  RunCoordinate;

      varVector<PropertyComponent<refVector>*>  RunGradient;

      varVector<uint> RunIdx, RunKIdx;

      typedef IDList<DistEvalObj,GeomType>    Type;

      IDList()
        : interactionTag(0), efunc(NULL), gfunc(NULL), bfunc(NULL),
          List(), RunCoordinate(), RunGradient(), RunIdx(), RunKIdx() {}

      IDList(const Type& IDL) { myError("copier for IDList is disabled!"); }

      Type& operator=(const Type& IDL) {
        interactionTag=IDL.interactionTag;
        efunc=IDL.efunc;
        gfunc=IDL.gfunc;
        bfunc=IDL.bfunc;
        List=IDL.List;
        return *this;
      }

      template <typename runDistEvalObj, typename runGeomType>
      Type& operator=(const IDList<runDistEvalObj,runGeomType>& IDL) {
        interactionTag=IDL.interactionTag;
        efunc=IDL.efunc;
        gfunc=IDL.gfunc;
        bfunc=IDL.bfunc;
        List=IDL.List;
        return *this;
      }

      Type& allocate(const uint& NL, const uint& NID) {
        List.allocate(NL);
        for(uint i=0;i<NL;++i)  List[i].allocate(NID);
        RunCoordinate.allocate(NID);
        RunGradient.allocate(NID);
        RunIdx.allocate(NID);
        RunKIdx.allocate(NID);
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

