
#ifndef _Random_Generator_Interface_H_
#define _Random_Generator_Interface_H_

#include <cstdlib>
#include <cassert>
#include <ctime>
#include "type.h"

namespace std {

  template <typename RandGeneratorType, typename T>
  class RandGenerator : public RandGeneratorType {

    public:

      typedef RandGenerator<RandGeneratorType,T>    Type;

      typedef RandGeneratorType                     ParentRNGType;

      RandGenerator() : ParentRNGType() {}

      RandGenerator(const Type& RNG) { assert(false); }

      RandGenerator(const uint& seed) : ParentRNGType(seed) {}

      void SetWithSeed(const uint& seed) {
        static_cast<ParentRNGType*>(this)->Init(seed);
      }

      void SetWithTime() { SetWithSeed(static_cast<uint>(time(0))); }

      const T& operator()() { return this->Default<T>(); }

  };
}

#endif

