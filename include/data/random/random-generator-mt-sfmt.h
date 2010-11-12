
#ifndef _Random_Generator_MT_SFMT_H_
#define _Random_Generator_MT_SFMT_H_

#include "data/basic/vector.h"
#include "data/basic/unique-parameter-128bit.h"

namespace std {

#ifdef HAVE_SSE2
  __m128i SFMT_SSE2_ParamMask;
#endif

}

#endif
