
#ifndef _Interaction_Calculate_H_
#define _Interaction_Calculate_H_

#include "data/interaction/interaction.h"

namespace std {

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void CalcInteraction(Interaction<T,DistBuffer,GeomType>& F,
                       const Vector<T>* X, const unsigned int* idx, T& Energy){
    F.EFunc(X,idx,F.prm.data,F.dbuff,F.geo,Energy);
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void CalcInteraction(Interaction<T,DistBuffer,GeomType>& F,
                       const Vector<T>* X, const unsigned int* idx,
                       Vector<T>* Gradient) {
    F.GFunc(X,idx,F.prm.data,F.dbuff,F.geo,Gradient);
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void CalcInteraction(Interaction<T,DistBuffer,GeomType>& F,
                       const Vector<T>* X, const unsigned int* idx,
                       T& Energy, Vector<T>* Gradient){
    F.BFunc(X,idx,F.prm.data,F.dbuff,F.geo,Energy,Gradient);
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void CalcInteraction(
      Vector<Interaction<T,DistBuffer,GeomType> >& F,
      const Vector<T>* X, const Vector<unsigned int>* idx, T& Energy) {
    for(unsigned int i=0;i<F.size;++i)
      CalcInteraction(F[i],X,idx[i].data,Energy);
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void CalcInteraction(
      Vector<Interaction<T,DistBuffer,GeomType> >& F,
      const Vector<T>* X,const Vector<unsigned int>* idx,Vector<T>* Gradient) {
    for(unsigned int i=0;i<F.size;++i)
      CalcInteraction(F[i],X,idx[i].data,Gradient);
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void CalcInteraction(
      Vector<Interaction<T,DistBuffer,GeomType> >& F,
      const Vector<T>* X,const Vector<unsigned int>* idx,
      T& Energy, Vector<T>* Gradient) {
    for(unsigned int i=0;i<F.size;++i)
      CalcInteraction(F[i],X,idx[i].data,Energy,Gradient);
  }

}

#include "data/interaction/list-interaction.h"

namespace std {

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void CalcInteraction(ListInteraction<T,DistBuffer,GeomType>& F,
                       const Vector<T>* X, const Vector<unsigned int>* idx,
                       T& Energy) {
    for(unsigned int i=0;i<F.NumList();++i)
      F.EFunc(X,idx[i].data,F.prm[i].data,F.dbuff,F.geo,Energy);
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void CalcInteraction(ListInteraction<T,DistBuffer,GeomType>& F,
                       const Vector<T>* X, const Vector<unsigned int>* idx,
                       Vector<T>* Gradient) {
    for(unsigned int i=0;i<F.NumList();++i)
      F.GFunc(X,idx[i].data,F.prm[i].data,F.dbuff,F.geo,Gradient);
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void CalcInteraction(ListInteraction<T,DistBuffer,GeomType>& F,
                       const Vector<T>* X, const Vector<unsigned int>* idx,
                       T& Energy, Vector<T>* Gradient) {
    for(unsigned int i=0;i<F.NumList();++i)
      F.BFunc(X,idx[i].data,F.prm[i].data,F.dbuff,F.geo,Energy,Gradient);
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void CalcInteraction(
      Vector<ListInteraction<T,DistBuffer,GeomType> >& F,
      const Vector<T>* X, const PropertyList<unsigned int>* idx, T& Energy) {
    for(unsigned int i=0;i<F.size;++i)
      CalcInteraction(F[i],X,idx[i].structure,Energy);
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void CalcInteraction(
      Vector<ListInteraction<T,DistBuffer,GeomType> >& F,
      const Vector<T>* X, const PropertyList<unsigned int>* idx,
      Vector<T>* Gradient) {
    for(unsigned int i=0;i<F.size;++i)
      CalcInteraction(F[i],X,idx[i].structure,Gradient);
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void CalcInteraction(
      Vector<ListInteraction<T,DistBuffer,GeomType> >& F,
      const Vector<T>* X, const PropertyList<unsigned int>* idx,
      T& Energy, Vector<T>* Gradient) {
    for(unsigned int i=0;i<F.size;++i)
      CalcInteraction(F[i],X,idx[i].structure,Energy,Gradient);
  }

}

#endif

