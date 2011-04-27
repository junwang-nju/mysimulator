
#ifndef _Random_Box_Muller_Interface_H_
#define _Random_Box_Muller_Interface_H_

#include "random/base/interface.h"

namespace mysimulator {

  template <typename UniformR>
  struct BoxMuller : public RandomBase {
  };

}

#endif

