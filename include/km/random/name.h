
/**
 * @file random/name.h
 * @brief name of various random number generators
 *
 * @author Jun | junwang.nju@gmail.com
 */

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

