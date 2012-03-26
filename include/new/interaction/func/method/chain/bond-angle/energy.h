
#ifndef _Interaction_Func_Method_Chain_Energy_H_
#define _Interaction_Func_Method_Chain_Energy_H_

#include "interaction/func/method/chain/-to-distance.h"
#include "interaction/func/method/chain/-to-angle.h"
#include "unique/64bit/interface.h"

namespace mysimulator {

  template <typename T, typename GeomType>
  void EFuncMethodChain(
      const Array1DContent<T>* X, const int* id, const Unique64Bit* P,
      const GeomType& Geo, T& Energy, Array1DContent<T>* tmvec,
      void (*efunc)(const T*,const Unique64Bit*,T*)) {
    unsigned int n=P[0].value<unsigned int>();
    T* DSQ=tmvec[0].start;
    T* D=DSQ+n-1;
    _ToChainDistance(X,id,n,Geo,tmvec,DSQ,D);
    T* csAngle=D+n-1;
    _ToChainAngle(X,id,n,Geo,tmvec,csAngle,DSQ,D);
    T ee;
    efunc(tmvec[0].start,P,&ee);
    Energy+=ee;
  }

}

#endif

