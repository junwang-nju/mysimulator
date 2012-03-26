
#ifndef _Interaction_Func_Method_Chain_ToDistance_H_
#define _Interaction_Func_Method_Chain_ToDistance_H_

#include "distance/calc.h"
#include "intrinsic-type/square-root.h"

namespace mysimulator {

  template <typename T, typename GeomType>
  void _ToChainDistance(
      const Array1DContent<T>* X, const int* id, const unsigned int& n,
      const GeomType& Geo, Array1DContent<T>* tmvec, T* DSQ, T* D) {
    int nid=id[0],pid;
    T td;
    for(unsigned int i=1,j=0;i<n;++j,++i) {
      pid=nid;
      nid=id[i];
      td=Distance(tmvec[i],X[pid],X[nid],Geo);
      DSQ[j]=td*td;
      D[j]=td;
    }
  }

}

#endif

