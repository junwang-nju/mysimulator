
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
                       Vector<T>* Gradient){
    F.GFunc(X,idx,F.prm.data,F.dbuff,F.geo,Gradient);
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void CalcInteraction(Interaction<T,DistBuffer,GeomType>& F,
                       const Vector<T>* X, const unsigned int* idx,
                       T& Energy, Vector<T>* Gradient){
    F.BFunc(X,idx,F.prm.data,F.dbuff,F.geo,Energy,Gradient);
  }

}

#endif

