
#ifndef _Random_MT_Interface_H_
#define _Random_MT_Interface_H_

#include "random/mt/name.h"

namespace mysimulator {

  template <MTMethodName MMN, unsigned int Fac=0U>
  struct MersenneTwister {

    public:

      typedef MersenneTwister<MMN,Fac>  Type;

      MersenneTwister() {}
      ~MersenneTwister() { Clear(*this); }

      bool IsValid() const { return false; }

    private:

      MersenneTwister(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <MTMethodName MMN, unsigned int Fac>
  void Clear(MersenneTwister<MMN,Fac>& R) {}

}

#include "random/mt/standard/interface.h"

#endif

