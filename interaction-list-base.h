
#ifndef _Interaction_List_Base_H_
#define _Interaction_List_Base_H_

#include "property-list.h"
#include "param-list.h"

namespace std {

  template <typename DistEvalObj, typename GeomType>
  class InteractionListBase {

    public:

      uint interactionTag;

      void (*efunc)(const VectorBase<refVector<double>*>&,
                    const VectorBase<uint>&,const VectorBase<uint>&,
                    const ParamList&,DistEvalObj&,const GeomType&,
                    double&);

      void (*gfunc)(const VectorBase<refVector<double>*>&,
                    const VectorBase<uint>&,const VectorBase<uint>&,
                    const ParamList&,DistEvalObj&,const GeomType&,
                    VectorBase<refVector<double>*>&);

      void (*bfunc)(const VectorBase<refVector<double>*>&,
                    const VectorBase<uint>&,const VectorBase<uint>&,
                    const ParamList&,DistEvalObj&,const GeomType&,
                    double&,VectorBase<refVector<double>*>&);

      PropertyList<varVector,refVector,uint>  List;
      PropertyList<varVector,refVector,uint>  KindIdx;

      //PropertyList<varVector,refVector,refVector<double>*> Coordinate;
      //PropertyList<varVector,refVector,refVector<double>*> Gradient;

      typedef InteractionListBase<DistEvalObj,GeomType>    Type;

      InteractionListBase()
        : interactionTag(0), efunc(NULL), gfunc(NULL), bfunc(NULL),
          List(), KindIdx() {}

      InteractionListBase(const Type& IL) {
        myError("copier for InteractionListBase is disabled!");
      }

      Type& operator=(const Type& IL) {
        interactionTag=IL.interactionTag;
        efunc=IL.efunc;
        gfunc=IL.gfunc;
        bfunc=IL.bfunc;
        List=IL.List;
        KindIdx=IL.KindIdx;
        return *this;
      }

      template <typename runDistEvalObj, typename runGeomType>
      Type& operator=(
        const InteractionListBase<runDistEvalObj,runGeomType>& IL) {
        interactionTag=IL.interactionTag;
        efunc=IL.efunc;
        gfunc=IL.gfunc;
        bfunc=IL.bfunc;
        List=IL.List;
        KindIdx=IL.KindIdx;
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
        List.BuildStructure(offset,size);
        KindIdx.BuildStructure(offset,size);
        return *this;
      }

      template <typename runDistEvalObj, typename runGeomType>
      Type& allocate(
        const InteractionListBase<runDistEvalObj,runGeomType>& IL) {
        uint nl=IL.List.size();
        uint nid=IL.List[0].size();
        return allocate(nl,nid);
      }

      void clear() {
        interactionTag=0;
        efunc=NULL;
        gfunc=NULL;
        bfunc=NULL;
        List.clear();
        KindIdx.clear();
      }

  };

}

#endif

