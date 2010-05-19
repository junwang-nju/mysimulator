
#ifndef _Random_Generator_H_
#define _Random_Generator_H_

#include "random-generator-uniform.h"
#include "random-generator-derived.h"
#include "random-generator-generic.h"

namespace std {

  typedef dSFMT<216091> UniformDbRNG;
  typedef BoxMuller<UniformDbRNG> GaussianRNG;

}

#endif

