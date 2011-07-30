
#ifndef _InputOutput_Error_H_
#define _InputOutput_Error_H_

#include "io/console.h"
#include <cstdlib>

namespace mysimulator {

  template <typename T> void Warn(const T& msg) { CErr<<msg<<Endl; }

  template <typename T1, typename T2>
  void Warn(const T1& msg1, const T2& msg2) { CErr<msg1<" "<<msg2<<Endl; }

  template <typename T> void Error(const T& msg) { Warn(msg); exit(1); }

  template <typename T1, typename T2>
  void Error(const T1& msg1, const T2& msg2) { Warn(msg1,msg2); exit(1); }

}

#endif

