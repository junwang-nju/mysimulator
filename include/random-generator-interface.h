
/**
 * @file random-generator-interface.h
 * @brief the basic interface for random generators
 *
 * @author Jun Wang (junwang.nju@gmail.com)
 */

#ifndef _Random_Generator_Interface_H_
#define _Random_Generator_Interface_H_

#include <cstdlib>
#include <ctime>
#include <cassert>
#include <iostream>

namespace std {

  template <typename RandGeneratorType, typename T>
  class RandGenerator : public RandGeneratorType {

    private:

      T tmTData;

    public:

      typedef RandGenerator<RandGeneratorType,T>    Type;

      typedef RandGeneratorType                     ParentRNGType;

      RandGenerator() : ParentRNGType() {}

      RandGenerator(const Type& RNG) { assert(false); }

      RandGenerator(const unsigned int seed) : ParentRNGType(seed) {}

      void SetWithSeed(const unsigned int seed) {
        static_cast<ParentRNGType*>(this)->Init(seed);
      }

      void SetWithTime() { SetWithSeed(static_cast<unsigned int>(time(0))); }

      const T& operator()() { return this->Default(tmTData); }

      void save(ostream& os) {
        static_cast<ParentRNGType*>(this)->saveStatus(os);
      }

      void load(istream& is) {
        static_cast<ParentRNGType*>(this)->loadStatus(is);
      }

  };
}

#endif

