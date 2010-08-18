
/**
 * @file random-generator-generic.h
 * @brief Modules for generic random generators
 *
 * This file contains some procedures which are generic for
 * all random generators.
 *
 * @author Jun Wang (junwang.nju@gmail.com)
 */

#ifndef _Random_Generator_Generic_H_
#define _Random_Generator_Generic_H_

#include <ctime>
#include "vector.h"

namespace std {

  /**
   * @brief initiate a generator with present time.
   *
   * The present time is converted as \c unsigned \c int which records
   * the seconds starting from a certain time to now. This \c unsigned 
   * \c int is used as the seed to initiate the random generator
   *
   * RNG is the type of the random generator
   *
   * @param rg [out] the random generator to be initialized
   * @return nothing
   */
  template <typename RNG>
  void initWithTime(RNG& rg) { rg.Init(static_cast<unsigned int>(time(0))); }

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

