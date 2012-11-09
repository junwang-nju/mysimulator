
#ifndef _Array_Interface_H_
#define _Array_Interface_H_

#include "array/def.h"

#include "array/general.h"
#include "array/general-value.h"
#include "array/intrinsic.h"

namespace std {

  template <typename T>
  void swap(mysimulator::Array<T>& A, mysimulator::Array<T>& B) {
    A.swap(B);
  }

}

#endif

