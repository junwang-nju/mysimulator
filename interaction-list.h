
#ifndef _ID_List_H_
#define _ID_List_H_

#include "property-list.h"
#include "param-list.h"

namespace std {

  template <typename DistEvalObj, typename GeomType>
  class IDList {

    public:

      uint interactionTag;

      void (*efunc)(const VectorBase<Property<refVector>*>&,
                    const VectorBase<uint>&,const VectorBase<uint>&,
                    const ParamList&,DistEvalObj&,const GeomType&,
                    double&);

      void (*gfunc)(const VectorBase<Property<refVector>*>&,
                    const VectorBase<uint>&,const VectorBase<uint>&,
                    const ParamList&,DistEvalObj&,const GeomType&,
                    VectorBase<Property<refVector>*>&);

      void (*bfunc)(const VectorBase<Property<refVector>*>&,
                    const VectorBase<uint>&,const VectorBase<uint>&,
                    const ParamList&,DistEvalObj&,const GeomType&,
                    double&,VectorBase<Property<refVector>*>&);

      PropertyList<varVector,uint>  List;
      PropertyList<varVector,uint>  KindIdx;

      PropertyList<varVector,Property<refVector>*> Coordinate;
      PropertyList<varVector,Property<refVector>*> Gradient;

      typedef IDList<DistEvalObj,GeomType>    Type;

      IDList()
        : interactionTag(0), efunc(NULL), gfunc(NULL), bfunc(NULL),
          List(), KindIdx(), Coordinate(), Gradient() {}

      IDList(const Type& IDL) { myError("copier for IDList is disabled!"); }

      Type& operator=(const Type& IDL) {
        interactionTag=IDL.interactionTag;
        efunc=IDL.efunc;
        gfunc=IDL.gfunc;
        bfunc=IDL.bfunc;
        List=IDL.List;
        KindIdx=IDL.KindIdx;
        Coordinate=IDL.Coordinate;
        Gradient=IDL.Gradient;
        return *this;
      }

      template <typename runDistEvalObj, typename runGeomType>
      Type& operator=(const IDList<runDistEvalObj,runGeomType>& IDL) {
        interactionTag=IDL.interactionTag;
        efunc=IDL.efunc;
        gfunc=IDL.gfunc;
        bfunc=IDL.bfunc;
        List=IDL.List;
        KindIdx=IDL.KindIdx;
        Coordinate=IDL.Coordinate;
        Gradient=IDL.Gradient;
        return *this;
      }

      Type& allocate(const uint& NL, const uint& NID) {
        varVector<uint> offset(NL),size(NL);
        offset[0]=0;
        size[0]=NID;
        for(uint i=1;i<NL;++i) {
          offset[i]=offset[i-1]+NID;
          size[i]=NID;
        }
        List.allocate(NL);
        KindIdx.allocate(NL);
        Coordinate.allocate(NL);
        Gradient.allocate(NL);
        List.BuildStructure(offset,size);
        KindIdx.BuildStructure(offset,size);
        Coordinate.BuildStructure(offset,size);
        Gradient.BuildStructure(offset,size);
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

