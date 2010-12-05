
#ifndef _Random_Generator_Regular_H_
#define _Random_Generator_Regular_H_

#include "data/random/random-generator-mt-dsfmt.h"
#include "data/random/random-generator-boxmuller.h"

namespace std {
  typedef dSFMT<216091> UniformDbRNG;

  typedef BoxMuller<UniformDbRNG> GaussianRNG;
}

#endif

