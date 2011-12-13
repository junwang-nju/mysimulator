
#ifndef _Object_Allocate_H_
#define _Object_Allocate_H_

#include "object/interface.h"
#include "pointer/allocate.h"

namespace mysimulator {

  template <typename T>
  void allocate(Object<T>& O) {
    release(O);
    allocate(static_cast<typename Object<T>::ParentType&>(O));
  }

  template <typename T1, typename T2>
  void _imprint_structure(Object<T1>& O, const Object<T2>& cO) {
    allocate(O);
    _imprint_structure(O(),cO());
  }

  template <typename T1, typename T2>
  void _imprint_structure(Object<T1>& O, const T2& d) {
    allocate(O);
    _imprint_structure(O(),d);
  }

  template <typename T1, typename T2>
  void _imprint_structure(T1& d, const Object<T2>& O) {
    assert(IsValid(O));
    _imprint_structure(d,O());
  }

  template <typename T>
  void imprint(Object<T>& O, const Object<T>& cO) {
    allocate(O);
    imprint(O(),cO());
  }

  template <typename T>
  void imprint(Object<T>& O, const T& d) {
    allocate(O);
    imprint(O(),d);
  }

  template <typename T>
  void imprint(T& d, const Object<T>& O) {
    assert(IsValid(O));
    imprint(d,O());
  }

}

#endif

