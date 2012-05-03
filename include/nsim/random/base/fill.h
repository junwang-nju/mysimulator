
#ifndef _Random_Base_Fill_H_
#define _Random_Base_Fill_H_

#include "random/base/interface.h"
#include "array/1d/interface.h"

namespace mysimulator {

  void Fill(Array1D<double>& V, RandomBase& Rnd, unsigned int n) {
    assert(n<=V.Size());
    for(unsigned int i=0;i<n;++i) V[i]=Rnd.Double();
  }

  void Fill(Array1D<unsigned int>& V, RandomBase& Rnd, unsigned int n) {
    assert(n<=V.Size());
    for(unsigned int i=0;i<n;++i) V[i]=Rnd.UInt();
  }

}

#include "array/2d/interface.h"

namespace mysimulator {

  template <typename T>
  void Fill(Array2D<T>& V, RandomBase& Rnd) {
    Fill(V._ldata,Rnd,V._ldata.Size());
  }

}

#endif

