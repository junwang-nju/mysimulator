
#ifndef _Interaction_Calculate_H_
#define _Interaction_Calculate_H_

#include "data/interaction/parameter-unit.h"
#include "data/interaction/simple.h"

namespace std {

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void CalcInteraction(
      SimpleInteraction<T,DistBuffer,GeomType>& F,
      const Vector<T>* X, const InteractionParameterUnit& P, T& Energy){
    if(P.enabled()!=0)
      F.EFunc(X,P.idx.data,P.prm.data,F.B,F.Geo,Energy,
              F.tmvec.structure,F.NumMerUnit());
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void CalcInteraction(
      SimpleInteraction<T,DistBuffer,GeomType>& F,
      const Vector<T>* X, const InteractionParameterUnit& P, 
      Vector<T>* Gradient) {
    if(P.enabled()!=0)
      F.GFunc(X,P.idx.data,P.prm.data,F.B,F.Geo,Gradient,
              F.tmvec.structure,F.NumMerUnit());
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void CalcInteraction(
      SimpleInteraction<T,DistBuffer,GeomType>& F,
      const Vector<T>* X, const InteractionParameterUnit& P, 
      T& Energy, Vector<T>* Gradient){
    if(P.enabled()!=0)
      F.BFunc(X,P.idx.data,P.prm.data,F.B,F.Geo,Energy,Gradient,
              F.tmvec.structure,F.NumMerUnit());
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void CalcInteraction(
      SimpleInteraction<T,DistBuffer,GeomType>& F,
      const Vector<T>* X, const Vector<InteractionParameterUnit>& P,
      T& Energy) {
    for(unsigned int i=0;i<P.size;++i)
      if(P[i].enabled()!=0)
        F.EFunc(X,P[i].idx.data,P[i].prm.data,F.B,F.Geo,Energy,
                F.tmvec.structure,F.NumMerUnit());
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void CalcInteraction(
      SimpleInteraction<T,DistBuffer,GeomType>& F,
      const Vector<T>* X, const Vector<InteractionParameterUnit>& P,
      Vector<T>* Gradient) {
    for(unsigned int i=0;i<P.size;++i)
      if(P[i].enabled()!=0)
        F.GFunc(X,P[i].idx.data,P[i].prm.data,F.B,F.Geo,Gradient,
                F.tmvec.structure,F.NumMerUnit());
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void CalcInteraction(
      SimpleInteraction<T,DistBuffer,GeomType>& F,
      const Vector<T>* X, const Vector<InteractionParameterUnit>& P,
      T& Energy, Vector<T>* Gradient) {
    for(unsigned int i=0;i<P.size;++i)
      if(P[i].enabled()!=0)
        F.BFunc(X,P[i].idx.data,P[i].prm.data,F.B,F.Geo,Energy,Gradient,
                F.tmvec.structure,F.NumMerUnit());
  }

}

#include "data/interaction/list.h"

namespace std {

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void CalcInteraction(
      ListInteraction<T,DistBuffer,GeomType>& F,
      const Vector<T>* X, const Vector<InteractionParameterUnit>& P,
      T& Energy) {
    assert(F.size==P.size);
    for(unsigned int i=0;i<F.size;++i)
      if(P[i].enabled()!=0)
        F[i].EFunc(X,P[i].idx.data,P[i].prm.data,F.B,F.Geo,Energy,
                   F[i].tmvec.structure,F.NumMerUnit());
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void CalcInteraction(
      ListInteraction<T,DistBuffer,GeomType>& F,
      const Vector<T>* X, const Vector<InteractionParameterUnit>& P,
      Vector<T>* Gradient){
    assert(F.size==P.size);
    for(unsigned int i=0;i<F.size;++i) {
      if(P[i].enabled()!=0)
        F[i].GFunc(X,P[i].idx.data,P[i].prm.data,F.B,F.Geo,Gradient,
                   F[i].tmvec.structure,F.NumMerUnit());
    }
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void CalcInteraction(
      ListInteraction<T,DistBuffer,GeomType>& F,
      const Vector<T>* X, const Vector<InteractionParameterUnit>& P,
      T& Energy, Vector<T>* Gradient) {
    assert(F.size==P.size);
    for(unsigned int i=0;i<F.size;++i)
      if(P[i].enabled()!=0)
        F[i].BFunc(X,P[i].idx.data,P[i].prm.data,F.B,F.Geo,Energy,Gradient,
                   F[i].tmvec.structure,F.NumMerUnit());
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void CalcInteraction(
      ListInteraction<T,DistBuffer,GeomType>& F,
      const Vector<T>* X, const PropertyList<InteractionParameterUnit>& P,
      T& Energy) {
    assert(F.size==P.nunit);
    for(unsigned int i=0;i<P.nunit;++i)
    for(unsigned int k=0;k<P[i].size;++k)
      if(P[i][k].enabled()!=0)
        F[i].EFunc(X,P[i][k].idx.data,P[i][k].prm.data,F.B,F.Geo,Energy,
                   F[i].tmvec.structure,F.NumMerUnit());
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void CalcInteraction(
      ListInteraction<T,DistBuffer,GeomType>& F,
      const Vector<T>* X, const PropertyList<InteractionParameterUnit>& P,
      Vector<T>* Gradient) {
    assert(F.size==P.nunit);
    for(unsigned int i=0;i<P.nunit;++i)
    for(unsigned int k=0;k<P[i].size;++k)
      if(P[i][k].enabled()!=0)
        F[i].GFunc(X,P[i][k].idx.data,P[i][k].prm.data,F.B,F.Geo,Gradient,
                   F[i].tmvec.structure,F.NumMerUnit());
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void CalcInteraction(
      ListInteraction<T,DistBuffer,GeomType>& F,
      const Vector<T>* X, const PropertyList<InteractionParameterUnit>& P,
      T& Energy, Vector<T>* Grad) {
    assert(F.size==P.nunit);
    for(unsigned int i=0;i<P.nunit;++i)
    for(unsigned int k=0;k<P[i].size;++k)
      if(P[i][k].enabled()!=0)
        F[i].BFunc(X,P[i][k].idx.data,P[i][k].prm.data,F.B,F.Geo,Energy,Grad,
                   F[i].tmvec.structure,F.NumMerUnit());
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void CalcInteraction(
      ListInteraction<T,DistBuffer,GeomType>& F,
      const Vector<T>* X, const Vector<Vector<InteractionParameterUnit> >& P,
      T& Energy){
    assert(F.size==P.size);
    for(unsigned int i=0;i<P.size;++i)
    for(unsigned int k=0;k<P[i].size;++k)
      if(P[i][k].enabled()!=0)
        F[i].EFunc(X,P[i][k].idx.data,P[i][k].prm.data,F.B,F.Geo,Energy,
                   F[i].tmvec.structure,F.NumMerUnit());
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void CalcInteraction(
      ListInteraction<T,DistBuffer,GeomType>& F,
      const Vector<T>* X, const Vector<Vector<InteractionParameterUnit> >& P,
      Vector<T>* Gradient) {
    assert(F.size==P.size);
    for(unsigned int i=0;i<P.size;++i)
    for(unsigned int k=0;k<P[i].size;++k)
      if(P[i][k].enabled()!=0)
        F[i].GFunc(X,P[i][k].idx.data,P[i][k].prm.data,F.B,F.Geo,Gradient,
                   F[i].tmvec.structure,F.NumMerUnit());
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void CalcInteraction(
      ListInteraction<T,DistBuffer,GeomType>& F,
      const Vector<T>* X, const Vector<Vector<InteractionParameterUnit> >& P,
      T& Energy, Vector<T>* Grad) {
    assert(F.size==P.size);
    for(unsigned int i=0;i<P.size;++i)
    for(unsigned int k=0;k<P[i].size;++k)
      if(P[i][k].enabled()!=0)
        F[i].BFunc(X,P[i][k].idx.data,P[i][k].prm.data,F.B,F.Geo,Energy,Grad,
                   F[i].tmvec.structure,F.NumMerUnit());
  }

}

namespace std {

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void CalcInteraction(
      SimpleInteraction<T,DistBuffer,GeomType>& F,
      const PropertyList<T>& X, const InteractionParameterUnit& P,
      T& Energy) {
    CalcInteraction(F,X.structure,P,Energy);
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void CalcInteraction(
      SimpleInteraction<T,DistBuffer,GeomType>& F,
      const PropertyList<T>& X, const InteractionParameterUnit& P,
      PropertyList<T>& Gradient) {
    CalcInteraction(F,X.structure,P,Gradient.srtucture);
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void CalcInteraction(
      SimpleInteraction<T,DistBuffer,GeomType>& F,
      const PropertyList<T>& X, const InteractionParameterUnit& P,
      T& Energy, PropertyList<T>& Gradient) {
    CalcInteraction(F,X.structure,P,Energy,Gradient.srtucture);
  }

  template <typename T, typename InteractionType>
  void CalcInteraction(
      InteractionType& F,
      const PropertyList<T>& X,const Vector<InteractionParameterUnit>& P,
      T& Energy) {
    CalcInteraction(F,X.structure,P,Energy);
  }

  template <typename T, typename InteractionType>
  void CalcInteraction(
      InteractionType& F,
      const PropertyList<T>& X, const Vector<InteractionParameterUnit>& P,
      PropertyList<T>& Gradient) {
    CalcInteraction(F,X.structure,P,Gradient.structure);
  }

  template <typename T, typename InteractionType>
  void CalcInteraction(
      InteractionType& F,
      const PropertyList<T>& X, const Vector<InteractionParameterUnit>& P,
      T& Energy, PropertyList<T>& Gradient) {
    CalcInteraction(F,X.structure,P,Energy,Gradient.structure);
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void CalcInteraction(
      ListInteraction<T,DistBuffer,GeomType>& F,
      const PropertyList<T>& X,const PropertyList<InteractionParameterUnit>& P,
      T& Energy) {
    CalcInteraction(F,X.structure,P,Energy);
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void CalcInteraction(
      ListInteraction<T,DistBuffer,GeomType>& F,
      const PropertyList<T>& X,const PropertyList<InteractionParameterUnit>& P,
      PropertyList<T>& Gradient) {
    CalcInteraction(F,X.structure,P,Gradient.structure);
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void CalcInteraction(
      ListInteraction<T,DistBuffer,GeomType>& F,
      const PropertyList<T>& X,const PropertyList<InteractionParameterUnit>& P,
      T& Energy, PropertyList<T>& Gradient) {
    CalcInteraction(F,X.structure,P,Energy,Gradient.structure);
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void CalcInteraction(
      ListInteraction<T,DistBuffer,GeomType>& F,
      const PropertyList<T>& X,
      const Vector<Vector<InteractionParameterUnit> >& P,
      T& Energy) {
    CalcInteraction(F,X.structure,P,Energy);
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void CalcInteraction(
      ListInteraction<T,DistBuffer,GeomType>& F,
      const PropertyList<T>& X,
      const Vector<Vector<InteractionParameterUnit> >& P,
      PropertyList<T>& Gradient) {
    CalcInteraction(F,X.structure,P,Gradient.structure);
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void CalcInteraction(
      ListInteraction<T,DistBuffer,GeomType>& F,
      const PropertyList<T>& X,
      const Vector<Vector<InteractionParameterUnit> >& P,
      T& Energy, PropertyList<T>& Gradient) {
    CalcInteraction(F,X.structure,P,Energy,Gradient.structure);
  }

}

#endif

