
#ifndef _Array_Interface_H_
#define _Array_Interface_H_

#include "array/def.h"

#include "array/general.h"
#include "array/general-value.h"
#include "array/intrinsic-simple.h"
#include "array/intrinsic-sse.h"
#include "array/intrinsic-direct-3d.h"

namespace mysimulator {

  template <typename T,ArrayKernelName K1,ArrayKernelName K2>
  void __imprint(Array<T,K1>& A, Array<T,K2> const& B) { A.imprint(B); }

}

namespace std {

  template <typename T>
  void swap(mysimulator::Array<T>& A, mysimulator::Array<T>& B) { A.swap(B); }

}

#include "array/operation/dot.h"
#include "array/operation/sum.h"
#include "array/operation/norm.h"
#include "array/operation/cross.h"

#endif

