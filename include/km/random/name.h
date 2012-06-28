
#ifndef _Random_Name_H_
#define _Random_Name_H_

namespace mysimulator {

  enum RandomName {
    MTStandardRNG=0,
    MTSFMTRNG,
    MTDSFMTRNG,
    BoxMullerRNG,
    UnknownRNG
  };

}

#endif

