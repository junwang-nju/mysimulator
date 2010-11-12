
#ifndef _Random_Generator_Operation_H_
#define _Random_Generator_Operation_H_

#include <ctime>

namespace std {

  template <typename RNG>
  void initWithTime(RNG& rg) { init(rg,static_cast<unsigned int>(time(0))); }

  template <typename RNG, typename T>
  void fillarray(RNG& rg, T* array, const unsigned int size,
                          const int off=iZero, const long step=lOne) {
    assert(IsAvailable(rg));
    assert(IsAvailable(array));
    for(unsigned int i=0,k=off;i<size;++i,k+=step) array[k]=rand<T>(rg);
  }

}

#include "data/basic/vector.h"

namespace std {

  template <typename RNG, typename T>
  void fillarray(RNG& rg, Vector<T>& v) { fillarray(rg,v.data,v.size); }

}

#endif
