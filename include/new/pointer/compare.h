
#ifndef _Pointer_Compare_H_
#define _Pointer_Compare_H_

#include "pointer/interface.h"

namespace mysimulator {

  template <typename T1, typename T2>
  bool IsSame(const Pointer<T1>& p1, const Pointer<T2>& p2) { return false; }

  template <typename T>
  bool IsSame(const Pointer<T>& p1, const Pointer<T>& p2) {
    return p1.ptr==p2.ptr;
  }

  template <typename T1, typename T2>
  bool IsSame(const Pointer<T1>& p, const T2* const& p2) { return false; }

  template <typename T>
  bool IsSame(const Pointer<T>& p, const T* const& p2) { return p.ptr==p2; }

  template <typename T1, typename T2>
  bool IsSame(const T2* const& p2, const Pointer<T1>& p) { return false; }

  template <typename T>
  bool IsSame(const T* const& p2, const Pointer<T>& p) { return IsSame(p,p2); }

}

#endif

