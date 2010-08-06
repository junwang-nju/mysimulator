/**
 * @file random-generator.h
 * @brief random generator
 *
 * This file contains the head files for random generator.
 *
 * @author Jun Wang (junwang.nju@gmail.com)
 */

#ifndef _Random_Generator_H_
#define _Random_Generator_H_

#include "random-generator-uniform.h"
#include "random-generator-derived.h"
#include "random-generator-generic.h"

namespace std {

  /**
   * @brief definition of random generator with uniform distribution
   *
   * This kind of generator may produce double-type value which is
   * uniformly distributed in [0,1). It is implemented with dSFMT method.
   */
  typedef dSFMT<216091> UniformDbRNG;

  /**
   * @brief definition of random generator with gaussian distribution
   *
   * This kind of generator may produce double-type value which takes
   * gaussian distribution with zero average and unit deviation. It is
   * implemented with Box-Muller method. The involved random generator
   * with uniform distribution is UniformDbRNG. 
   */
  typedef BoxMuller<UniformDbRNG> GaussianRNG;

}

#endif

