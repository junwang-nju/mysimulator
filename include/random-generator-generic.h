
#ifndef _Random_Generator_H_
#define _Random_Generator_H_

#include <ctime>
#include "vector.h"

namespace std {

  template <typename RNG>
  void initWithtime(RNG& rg) { rg.init(static_cast<unsigned int>(time(0))); }

  template <typename RNG, typename T>
  void fillarray(RNG& rg, T* array, const unsigned int size,
                          const unsigned int off=uZero,
                          const unsigned int step=uOne) {
    assert(IsAvailable(rg));
    for(unsigned int i=0,k=off;i<size;++i,k+=step)  array[k]=rand<T>(rg);
  }

  template <typename RNG, typename T>
  void fillarray(RNG& rg, Vector<T>& v) {
    assert(IsAvailable(v));
    fillarray(rg,v.data,v.size);
  }

}

#endif

