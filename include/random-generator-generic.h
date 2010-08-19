
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

  /**
   * @brief fill an array with a generator
   *
   * The elements in the array are assigned with the numbers produced by
   * the generator sequentially. The output type is determined by the
   * type of element in array.
   *
   * RNG is the type of the random generator. T is the type of element
   * in the array.
   *
   * @param rg [in,out] The random generator
   * @param array [out] the array to accept the random numbers
   * @param size [in] the number of elements to be filled in array
   * @param off [in] the offset for the first elements in array, which
   *                 takes the default value of uZero.
   * @param step [in] the separation between elements in array, which takes
   *                  the default value of uOne
   * @return nothing
   */
  template <typename RNG, typename T>
  void fillarray(RNG& rg, T* array, const unsigned int size,
                          const unsigned int off=uZero,
                          const unsigned int step=uOne) {
    assert(IsAvailable(rg));
    for(unsigned int i=0,k=off;i<size;++i,k+=step)  array[k]=rand<T>(rg);
  }

  /**
   * @brief fill a vector with a generator
   *
   * It is implemented with the operation to fill an array with the input
   * generator.
   *
   * RNG is the type of the random generator. T is the type of element
   * in the array.
   *
   * @param rg [in,out] The random generator
   * @param v [out] the vector with T type elements
   * @return nothing
   */
  template <typename RNG, typename T>
  void fillarray(RNG& rg, Vector<T>& v) {
    assert(IsAvailable(v));
    fillarray(rg,v.data,v.size);
  }

}

#endif

