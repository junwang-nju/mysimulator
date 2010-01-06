
/**
 * @file random-generator.h
 * @brief random generator definition
 *
 * @author Jun Wang (junwang.nju@gmail.com)
 */

#ifndef _Random_Generator_H_
#define _Random_Generator_H_

#include "random-generator-interface.h"
#include "random-generator-uniform.h"
#include "random-generator-derived.h"

namespace std {

  typedef RandGenerator<dSFMT<216091>,double> UniformDbRNG;

  typedef RandGenerator<BoxMuller<UniformDbRNG>,double> GaussianRNG;

}

#endif

