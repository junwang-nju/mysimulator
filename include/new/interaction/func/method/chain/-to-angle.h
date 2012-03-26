
#ifndef _Interaction_Func_Method_Chain_ToAngle_H_
#define _Interaction_Func_Method_Chain_ToAngle_H_

#include "distance/calc.h"

namespace mysimulator {

  template <typename T, typename GeomType>
  void _ToChainAngle(
      const Array1DContent<T>* X, const int* id, const unsigned int& n,
      const GeomType& Geo, Array1DContent<T>* tmvec, T* csAngle,
      const T* DSQ, const T* D) {
    T td;
    for(unsigned int i=2,j=0;i<n;++i,++j) {
      td=DistanceSQ(tmvec[n+1],X[id[j]],X[id[i]],Geo);
      csAngle[j]=(DSQ[j]+DSQ[j+1]-td)/(D[j]*D[j+1])*0.5;
    }
  }

}

#endif

