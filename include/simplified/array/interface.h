
#ifndef _Array_Interface_H_
#define _Array_Interface_H_

#include "array/def.h"

#include "array/general.h"
#include "array/general-value.h"
#include "array/intrinsic-simple.h"
#include "array/intrinsic-sse.h"

namespace mysimulator {

  template <typename T>
  void __imprint(Array<T>& A, Array<T> const& B) { A.imprint(B); }

}

namespace std {

  template <typename T>
  void swap(mysimulator::Array<T>& A, mysimulator::Array<T>& B) { A.swap(B); }

}

#endif

