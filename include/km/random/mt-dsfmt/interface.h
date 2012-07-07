
#ifndef _Random_MT_DSFMT_Interface_H_
#define _Random_MT_DSFMT_Interface_H_

#include "random/interface.h"

namespace mysimulator {

  template <unsigned int Fac>
  struct MersenneTwisterDSFMT : public Random {

    public:

      typedef MersenneTwisterDSFMT<Fac>   Type;
      typedef Random  ParentType;

    private:

      MersenneTwisterDSFMT(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

}

#endif

