
#ifndef _Parameter_Neighbor_List_Operation_H_
#define _Parameter_Neighbor_List_Operation_H_

#include "data/interaction/parameter-neighbor-list.h"
#include "data/interaction/parameter-unit.h" 
#include "operation/geometry/distance-calc.h"

namespace std {

  template <template <typename> class PShape, typename T, typename GeomType>
  bool Check(ParameterWNeighborList<PShape,T>& P,
             const Vector<T>* X, const GeomType& Geo) {
    bool ifup=false;
    Vector<T> V;
    imprint(V,X[0]);
    for(unsigned int i=0;i<P.XBackup.size;++i) {
      Displacement(P.XBackup[i],X[i],V,Geo);
      if(asum(V)>P.BufferDistance())  { ifup=true; break; }
    }
    return ifup;
  }

  template <template <typename> class PShape, typename T, typename GeomType>
  void init(ParameterWNeighborList<PShape,T>& P,
            PropertyList<T>& X, const T& cf, const T& bd, const GeomType& Geo){
    assert(IsAvailable(P.possibleParameter));
    if(!IsAvailable(P.ParameterID)) imprint(P.ParameterID,P.possibleParameter);
    if(!IsAvailable(P.XBackup)) imprint(P.XBackup,X);
    P.XBackup[0][0]=X[0][0]+P.ListRadius()*2.;
    if((!IsAvailable(P.property))&&(P.property.size<3)) allocate(P.property,3);
    P.Cutoff()=cf;
    P.BufferDistance()=bd;
    P.ListRadius()=cf+bd;
    Update(P,X.structure,Geo);
  }

  template <typename T, typename GeomType>
  void update(ParameterWNeighborList<Vector,T>& P,
              const Vector<T>* X, const GeomType& Geo) {
    if(Check(P,X,Geo)) {
      unsigned int nP=0;
      T tmdist;
      Vector<T> V;
      imprint(V,X[0]);
      for(unsigned int i=0;i<P.possibleParameter.size;++i) {
        if(P.possibleParameter[i].idx.size>2)   continue;
        tmdist=Distance(X[P.possibleParameter[i].idx[0]],
                        X[P.possibleParameter[i].idx[1]],V,Geo);
        if(tmdist<P.ListRadius())   P.ParameterID[nP++]=i;
      }
      allocate(static_cast<Vector<InteractionParameterUnit>&>(P),nP);
      for(unsigned int i=0;i<nP;++i)
        refer(P[i],P.possibleParameter[P.ParameterID[i]]);
      for(unsigned int i=0;i<P.XBackup.nunit;++i) copy(P.XBackup[i],X[i]);
    }
  }

  template <typename T, typename GeomType>
  void update(
      ParameterWNeighborList<PropertyList,T>& P,
      Vector<T>* X, const GeomType& Geo) {
    if(Check(P,X,Geo)) {
      Vector<unsigned int> sz;
      allocate(sz,P.ParameterID.nunit);
      copy(sz,0);
      T tmdist;
      Vector<T> V;
      imprint(V,X[0]);
      for(unsigned int i=0;i<P.possibleParameter.nunit;++i)
      for(unsigned int k=0;k<P.possibleParameter[i].size;++k){
        if(P.possibleParameter[i][k].idx.size>2)   continue;
        tmdist=Distance(X[P.possibleParameter[i][k].idx[0]],
                        X[P.possibleParameter[i][k].idx[1]],V,Geo);
        if(tmdist<P.ListRadius())   P.ParameterID[i][sz[i]++]=k;
      }
      allocate(static_cast<Vector<InteractionParameterUnit>&>(P),sz);
      for(unsigned int i=0;i<P.nunit;++i)
      for(unsigned int k=0;k<P[i].size;++k)
        refer(P[i][k],P.possibleParameter[i][P.ParameterID[i][k]]);
      for(unsigned int i=0;i<P.XBackup.nunit;++i) copy(P.XBackup[i],X[i]);
    }
  }

}

#endif

