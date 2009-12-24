
#ifndef _Interaction_LIst_H_
#define _Interaction_LIst_H_

#include "interaction-list-base.h"

namespace std {

  template <typename DistEvalObj, typename GeomType, uint BindMode>
  class InteractionList {
    public:
      InteractionList() {
        myError("Interaction List with present Mode is disabled!");
      }
  };

  enum DataBindType {
    LooseDataBinding=0,
    TightDataBinding
  };

  template <typename DistEvalObj, typename GeomType>
  class InteractionList<DistEvalObj,GeomType,LooseDataBinding>
    : public InteractionListBase<DistEvalObj,GeomType> {
    public:
      typedef InteractionListBase<DistEvalObj,GeomType>         ParentType;
      typedef InteractionList<DistEvalObj,GeomType,LooseDataBinding>  Type;

      varVector<refVector<double>*>   Coordinate;
      varVector<refVector<double>*>   Gradient;

      InteractionList() : ParentType(), Coordinate(), Gradient() {}
      InteractionList(const Type& IL) {
        myError("copier for interaction list is prohibited!");
      }
      Type& operator=(const Type& IL) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(IL));
        return *this;
      }
      template <typename rDistEvalObj, typename rGeomType, uint rBindMode>
      Type& operator=(
        const InteractionList<rDistEvalObj,rGeomType,rBindMode>& IL) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<InteractionListBase<rDistEvalObj,rGeomType>*>(IL));
        return *this;
      }
      Type& allocate(const uint& nl, const uint& nid) {
        static_cast<ParentType*>(this)->allocate(nl,nid);
        Coordinate.allocate(nid);
        Gradient.allocate(nid);
        return *this;
      }
      template <typename rDistEvalObj, typename rGeomType>
      Type& allocate(
        const InteractionListBase<runDistEvalObj,runGeomType>& IL) {
        uint nl=IL.List.size();
        uint nid=IL.List[0].size();
        return allocate(nl,nid);
      }
      void BuildCoordinateBinding(
        const VectorBase<refVector<double> >& rCoordinate,
        const uint& I) {
        uint nid=this->List[I].size();
        for(uint i=0;i<nid;++i)
          Coordinate[i]=&rCoordinate[this->List[I][i]];
      }
      void BuildGradientBinding(
        const VectorBase<refVector<double> >& rGradient,
        const uint& I) {
        uint nid=this->List[I].size();
        for(uint i=0;i<nid;++i)
          Gradient[i]=&rGradient[this->List[I][i]];
      }
      void clear() {
        Coordinate.clear();
        Gradient.clear();
        static_cast<ParentType*>(this)->clear();
      }
  };

  template <typename DistEvalObj, typename GeomType>
  class InteractionList<DistEvalObj,GeomType,TightDataBinding>
    : public InteractionListBase<DistEvalObj,GeomType> {
    public:
      typedef InteractionList<DistEvalObj,GeomType,LooseDataBinding>  Type;
      typedef InteractionListBase<DistEvalObj,GeomType>         ParentType;
      PropertyList<varVector,refVector,refVector<double>*>  Coordinate;
      PropertyList<varVector,refVector,refVector<double>*>  Gradient;

      InteractionList() : ParentType(), Coordinate(), Gradient() {}
      InteractionList(const Type& IL) {
        myError("copier for interaction list is prohibited!");
      }
      Type& operator=(const Type& IL) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(IL));
        return *this;
      }
      Type& allocate(const uint& nl, const uint& nid) {
        static_cast<ParentType*>(this)->allocate(nl,nid);
        varVector<uint> offset(nl),size(nl);
        offset[0]=0;
        size[0]=nid;
        for(uint i=1;i<nl;++i) {
          offset[i]=offset[i-1]+nid;
          size[i]=nid;
        }
        Coordinate.allocate(nl);
        Gradient.allocate(nl);
        Coordinate.BuildStructure(offset,size);
        Gradient.BuildStructure(offset,size);
        return *this;
      }
      template <typename rDistEvalObj, typename rGeomType>
      Type& allocate(
        const InteractionListBase<runDistEvalObj,runGeomType>& IL) {
        uint nl=IL.List.size();
        uint nid=IL.List[0].size();
        return allocate(nl,nid);
      }
      void BuildCoordinateBinding(
        const VectorBase<refVector<double> >& rCoordinate) {
        uint n=this->List.size(),nid;
        for(uint i=0;i<n;++i) {
          nid=this->List[i].size();
          for(uint k=0;k<nid;++k)
            Coordinate[i][k]=&rCoordinate[this->List[i][k]];
        }
      }
      void BuildGradientBinding(
        const VectorBase<refVector<double> >& rGradient) {
        uint n=this->List.size(),nid;
        for(uint i=0;i<n;++i) {
          nid=this->List[i].size();
          for(uint k=0;k<nid;++k)
            Gradient[i][k]=&rGradient[this->List[i][k]];
        }
      }
      void clear() {
        Coordinate.clear();
        Gradient.clear();
        static_cast<ParentType*>(this)->clear();
      }
  };

}

#endif

